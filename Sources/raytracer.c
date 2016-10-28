/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 15:41:19 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/28 14:23:16 by jubarbie         ###   ########.fr       */
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
	RAY_POS = fill_vector(CAM_POS.x, CAM_POS.y, CAM_POS.z);
	VW_UP_LEFT = sub_vectors(add_vectors(add_vectors(CAM_POS,
		time_vector(CAM_DIR, VW_DIST)), time_vector(CAM_UP, VW_HEIGHT / 2.0)),
		time_vector(CAM_RIGHT, VW_WIDTH / 2.0));
}

static void	init_ray(t_env *e, t_param *param)
{
	DIST = DIST_MAX;
	COLOR = 0x000000;
	RAY_DIR = unit_vector(add_vectors(VW_UP_LEFT, sub_vectors(time_vector(
					CAM_RIGHT, GAP_X * X), time_vector(CAM_UP, GAP_Y * Y))));
}

static void	apply_light(t_env *e, t_param *param)
{
	t_list		*lst_light;
	t_object	*light;
	//t_list		*lst_obj;
	//t_object	*obj;
	double		angle;
	t_hsv		hsv;
	
	lst_light = e->scene->light;
	while (lst_light)
	{
		light = (t_object *)lst_light->content;
		angle = angle_vectors(sub_vectors(light->pos, RAY), sub_vectors(e->scene->cam_pos, RAY));
		sphere(param, light);
		/*lst_obj = ENV->scene->obj;
		  while (lst_obj)
		  {
		  obj = (t_object *)lst_obj->content;
		  if (obj != OBJ)

		  lst_obj = lst_obj->next;
		  }*/
		//printf("a: %lf\n", angle);
		if (cos(angle) > 0 && L)
		{
			rgb_to_hsv(COLOR, &hsv.h, &hsv.s, &hsv.v);
			COLOR = hsv_to_rgb(hsv.h, hsv.s, hsv.v - cos(angle) * cos(angle) * norm_vector(sub_vectors(RAY, light->pos)) / 1.4);
		}
		lst_light = lst_light->next;
	}
}

void		*raytracer(void *arg)
{
	t_param		*param;
	t_list		*lst_obj;
	t_object	*obj;

	param = (t_param *)arg;
	init_param(param, ENV);
	while (++Y < (TH + 1) * WIN_HEIGHT / NB_TH)
	{
		X = -1;
		while (++X < WIN_WIDTH)
		{
			lst_obj = ENV->scene->obj;
			OBJ = (t_object *)lst_obj->content;
			init_ray(ENV, param);
			while (lst_obj)
			{
				obj = (t_object *)lst_obj->content;
				if (!ft_strcmp(obj->type, "sphere"))
					sphere(param, obj);
				if (!ft_strcmp(obj->type, "plane"))
					plane(param, obj);

				lst_obj = lst_obj->next;
			}
			apply_light(ENV, param);
			img_put_pixel(ENV, X, Y, COLOR);
		}
	}
	pthread_exit(0);
}
