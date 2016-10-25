/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 15:41:19 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/25 19:06:47 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_param(t_param *param, t_env *e)
{
	Y = TH * (WIN_HEIGHT / NB_TH) - 1;
	CAM_DIR = unit_vector(fill_vector(-CAM_POS.x, -CAM_POS.y, -CAM_POS.z));
	CAM_UP = unit_vector(fill_vector(0, 1, 0));
	CAM_RIGHT = unit_vector(perp_vector(CAM_DIR, CAM_UP));
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

void		*raytracer(void *arg)
{
	t_param		*param;
	t_list		*elem;
	t_object	*obj;

	param = (t_param *)arg;
	init_param(param, ENV);
	while (++Y < (TH + 1) * WIN_HEIGHT / NB_TH)
	{
		X = -1;
		while (++X < WIN_WIDTH)
		{
			elem = ENV->scene->obj;
			OBJ = (t_object *)elem->content;
			init_ray(ENV, param);
			while (elem)
			{
				obj = (t_object *)elem->content;
				if (!ft_strcmp(obj->type, "sphere"))
					sphere(param, obj);
				elem = elem->next;
			}
			img_put_pixel(ENV, X, Y, COLOR);
		}
	}
	pthread_exit(0);
}
