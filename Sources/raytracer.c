/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 15:41:19 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/08 16:13:21 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_param(t_param *param, t_env *e)
{
	Y = TH * (WIN_HEIGHT / NB_TH) - 1;
	CAM_UP = unit_v3d(cross_v3d(CAM_RIGHT, CAM_DIR));
	CAM_DIR = unit_v3d(v3d(-CAM_POS.x, -CAM_POS.y, -CAM_POS.z));
	CAM_RIGHT = unit_v3d(cross_v3d(CAM_DIR, CAM_UP));
	CAM_UP = unit_v3d(cross_v3d(CAM_DIR, CAM_RIGHT));
	VW_RAY.pos = v3d(CAM_POS.x, CAM_POS.y, CAM_POS.z);
	VW_UP_LEFT = sub_v3d(add_v3d(add_v3d(CAM_POS,
		smul_v3d(CAM_DIR, VW_DIST)), smul_v3d(CAM_UP, VW_HEIGHT / 2.0)),
		smul_v3d(CAM_RIGHT, VW_WIDTH / 2.0));
}

static void	init_vw_ray(t_env *e, t_param *param)
{
	VW_RAY.obj = NULL;
	VW_RAY.dist = DIST_MAX;
	VW_RAY.dir = unit_v3d(sub_v3d(add_v3d(VW_UP_LEFT, sub_v3d(smul_v3d(
					CAM_RIGHT, GAP_X * X), smul_v3d(CAM_UP, GAP_Y * Y))), CAM_POS));
}

static void	init_light_ray(t_param *param, t_object *light)
{
	PHO_RAY.pos = light->pos;
	PHO_RAY.dist = DIST_MAX;
	PHO_RAY.dir = unit_v3d(sub_v3d(PHO_RAY.pos, VW_RAY.inter));
	PHO_RAY.obj = NULL;
	if (VW_RAY.obj && VW_RAY.obj->type == 2)
			param->norm = v3d(VW_RAY.obj->param[0], VW_RAY.obj->param[1]
				, VW_RAY.obj->param[2]);
	else if (VW_RAY.obj)
		param->norm = sub_v3d(VW_RAY.obj->pos, VW_RAY.inter);
}

static void	apply_light(t_env *e, t_param *param)
{
	t_list		*lst_light;
	t_object	*light;
	t_list		*lst_obj;
	t_object	*obj;
	float		angle;
	t_hsv		hsv;
	float		v;
	float		shadow;

	v = 0.0;
	shadow = 0.0;
	lst_light = e->scene->light;
	while (lst_light)
	{
		light = (t_object *)lst_light->content;
		lst_obj = e->scene->obj;
		init_light_ray(param, light);
		angle = cos_v3d(sub_v3d(VW_RAY.obj->pos, VW_RAY.inter), PHO_RAY.dir);
		while (lst_obj)
		{
			obj = (t_object *)lst_obj->content;
			if (obj != VW_RAY.obj)
				(*(e->obj_fct[obj->type]))(obj, &PHO_RAY);
			lst_obj = lst_obj->next;
		}
		rgb_to_hsv(VW_RAY.obj->color, &hsv.h, &hsv.s, &hsv.v);
		if (angle <= 0)
		{
			v += -angle * 0.6;
			if (PHO_RAY.obj && PHO_RAY.obj != VW_RAY.obj
			&& PHO_RAY.dist > length_v3d(sub_v3d(PHO_RAY.pos, VW_RAY.inter)))
				shadow += 0.05;
		}
		lst_light = lst_light->next;
	}
	COLOR = hsv_to_rgb(hsv.h, hsv.s, 0.2 + v - shadow);
}

void		*raytracer(void *arg)
{
	t_param		*param;
	t_list		*lst_obj;
	t_object	*obj;
	t_env		*e;

	param = (t_param *)arg;
	init_param(param, ENV);
	e = ENV;
	while (++Y < (TH + 1) * WIN_HEIGHT / NB_TH)
	{
		X = -1;
		while (++X < WIN_WIDTH)
		{
			lst_obj = ENV->scene->obj;
			init_vw_ray(ENV, param);
			while (lst_obj)
			{
				obj = (t_object *)lst_obj->content;
				(*(e->obj_fct[obj->type]))(obj, &VW_RAY);
				lst_obj = lst_obj->next;
			}
			COLOR = VW_RAY.obj ? VW_RAY.obj->color : 0;
			(VW_RAY.obj && L) ? apply_light(ENV, param) : 0;
			img_put_pixel(ENV, X, Y, COLOR);
		}
	}
	pthread_exit(0);
}
