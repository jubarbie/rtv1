/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 15:41:19 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/28 17:15:44 by jubarbie         ###   ########.fr       */
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
	VW_RAY.dist = DIST_MAX;
	COLOR = 0x000000;
	VW_RAY.dir = unit_vector(add_vectors(VW_UP_LEFT, sub_vectors(time_vector(
					CAM_RIGHT, GAP_X * X), time_vector(CAM_UP, GAP_Y * Y))));
}

static void	init_light_ray(t_param *param)
{
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

	init_light_ray(param);	
	lst_light = e->scene->light;
	while (lst_light)
	{
		light = (t_object *)lst_light->content;
		lst_obj = ENV->scene->obj;
		while (lst_obj)
		{
			obj = (t_object *)lst_obj->content;
			if (obj != VW_RAY.obj)
			{
				sphere(param, light, &PHO_RAY);
				if (PHO_RAY.obj && PHO_RAY.obj != VW_RAY.obj)
				{
					COLOR = 0;
					break;
				}
				else
				{
					angle = angle_vectors(PHO_RAY.dir, VW_RAY.dir);
					if (cos(angle) > 0 && L)
					{
						rgb_to_hsv(COLOR, &hsv.h, &hsv.s, &hsv.v);
						COLOR = hsv_to_rgb(hsv.h, hsv.s, hsv.v - cos(angle) *
							   cos(angle) / 4);
					}

				}
			}
			lst_obj = lst_obj->next;
		}
		lst_light = lst_light->next;
	}
}

void		*raytracer(void *arg)
{
	t_param		*param;
	t_list		*lst_obj;
	t_object	*obj;
	int			inter;

	param = (t_param *)arg;
	init_param(param, ENV);
	COLOR = 0;
	while (++Y < (TH + 1) * WIN_HEIGHT / NB_TH)
	{
		X = -1;
		while (++X < WIN_WIDTH)
		{
			lst_obj = ENV->scene->obj;
			//OBJ = (t_object *)lst_obj->content;
			init_vw_ray(ENV, param);
			inter = 0;
			while (lst_obj)
			{
				obj = (t_object *)lst_obj->content;
				if (!ft_strcmp(obj->type, "sphere"))
					inter += sphere(param, obj, &param->vw_ray);
				//if (!ft_strcmp(obj->type, "plane"))
				//	plane(param, obj);

				lst_obj = lst_obj->next;
			}
			inter ? apply_light(ENV, param) : 0;
			img_put_pixel(ENV, X, Y, COLOR);
		}
	}
	pthread_exit(0);
}
