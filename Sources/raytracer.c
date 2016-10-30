/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 15:41:19 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/30 17:52:07 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_param(t_param *param, t_env *e)
{
	Y = TH * (WIN_HEIGHT / NB_TH) - 1;
	CAM_UP = unit_vector(fill_vector(0, 1, 0));
	CAM_DIR = unit_vector(fill_vector(-CAM_POS.x, -CAM_POS.y, -CAM_POS.z));
	CAM_RIGHT = unit_vector(perp_vector(CAM_DIR, CAM_UP));
	CAM_UP = unit_vector(perp_vector(CAM_DIR, CAM_RIGHT));
	VW_RAY.pos = fill_vector(CAM_POS.x, CAM_POS.y, CAM_POS.z);
	VW_UP_LEFT = sub_vectors(add_vectors(add_vectors(CAM_POS,
		time_vector(CAM_DIR, VW_DIST)), time_vector(CAM_UP, VW_HEIGHT / 2.0)),
		time_vector(CAM_RIGHT, VW_WIDTH / 2.0));
}

static void	init_vw_ray(t_env *e, t_param *param)
{
	VW_RAY.obj = NULL;
	VW_RAY.dist = DIST_MAX;
	VW_RAY.dir = unit_vector(add_vectors(VW_UP_LEFT, sub_vectors(time_vector(
					CAM_RIGHT, GAP_X * X), time_vector(CAM_UP, GAP_Y * Y))));
}

static void	init_light_ray(t_param *param, t_object *light)
{
	PHO_RAY.pos = light->pos;
	PHO_RAY.dist = DIST_MAX;
	PHO_RAY.dir = unit_vector(sub_vectors(VW_RAY.inter, PHO_RAY.pos));
	PHO_RAY.obj = NULL;
}

static void	apply_light(t_env *e, t_param *param)
{
	t_list		*lst_light;
	t_object	*light;
	t_list		*lst_obj;
	t_object	*obj;
	double		angle;
	t_hsv		hsv;
	double		v;

	v = 0.0;
	lst_light = e->scene->light;
	while (lst_light)
	{
		light = (t_object *)lst_light->content;
		lst_obj = e->scene->obj;
		init_light_ray(param, light);
		angle = angle_vectors(sub_vectors(VW_RAY.obj->pos, VW_RAY.inter), PHO_RAY.dir);
		while (lst_obj)
		{
			obj = (t_object *)lst_obj->content;
			if (obj != VW_RAY.obj && !ft_strcmp(obj->type, "sphere"))
				sphere(obj, &PHO_RAY);
			if (obj != VW_RAY.obj && !ft_strcmp(obj->type, "plane"))
				plane(obj, &PHO_RAY);
			if (obj != VW_RAY.obj && !ft_strcmp(obj->type, "cylinder"))
				cylinder(obj, &PHO_RAY);
			lst_obj = lst_obj->next;
		}
		if (angle < 0)
		{
			rgb_to_hsv(VW_RAY.obj->color, &hsv.h, &hsv.s, &hsv.v);
			v += -angle * 0.6;
			if (PHO_RAY.obj && PHO_RAY.obj != VW_RAY.obj
			&& PHO_RAY.dist > norm_vector(sub_vectors(PHO_RAY.pos, VW_RAY.inter)))
				v -= 0.05;
		}
		lst_light = lst_light->next;
	}
	COLOR = hsv_to_rgb(hsv.h, hsv.s, 0.2 + v);
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
				if (!ft_strcmp(obj->type, "sphere"))
					sphere(obj, &VW_RAY);
				if (!ft_strcmp(obj->type, "plane"))
					plane(obj, &VW_RAY);
				if (!ft_strcmp(obj->type, "cylinder"))
					cylinder(obj, &VW_RAY);
				lst_obj = lst_obj->next;
			}
			COLOR = VW_RAY.obj ? VW_RAY.obj->color : 0;
			(VW_RAY.obj && L) ? apply_light(ENV, param) : 0;
			img_put_pixel(ENV, X, Y, COLOR);
		}
	}
	pthread_exit(0);
}
