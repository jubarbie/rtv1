/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 15:41:19 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/24 14:36:25 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	update_param(t_param *param, t_env *e)
{
	t_vector	vw_center;
	t_vector	vw_c_up;

	RAY_POS = fill_vector(CAM_POS.x, CAM_POS.y, CAM_POS.z);
	GAP_X = VW_WIDTH / (double)WIN_WIDTH;
	GAP_Y = VW_HEIGHT / (double)WIN_HEIGHT;	
	vw_center = add_vectors(CAM_POS, time_vector(CAM_DIR, VW_DIST));
	vw_c_up = add_vectors(vw_center, time_vector(CAM_UP, VW_HEIGHT / 2.0));
	VW_UP_LEFT = sub_vectors(vw_c_up, time_vector(CAM_RIGHT, VW_WIDTH / 2.0)); 
	RAY_DIR = unit_vector(add_vectors(VW_UP_LEFT, sub_vectors(time_vector(CAM_RIGHT,
						GAP_X * X), time_vector(CAM_UP, GAP_Y * Y))));
	if (D == 3)
	{
		print_vector(CAM_POS, "CAM_POS");
		print_vector(CAM_DIR, "CAM_DIR");
		print_vector(CAM_UP, "CAM_UP");
		print_vector(CAM_RIGHT, "CAM_RIGHT");
		print_vector(VW_UP_LEFT, "VW_UP_LEFT");
	}
}

void	*raytracer(void *arg)
{
	t_env		*e;
	t_param		*param;
	t_list		*elem;
	t_object	*obj;

	param = (t_param *)arg;
	e = ENV;
	Y = TH * (WIN_HEIGHT / NB_TH) - 1;
	while (++Y < (TH + 1) * WIN_HEIGHT / NB_TH)
	{
		X = -1;
		while (++X < WIN_WIDTH)
		{
			elem = e->scene->obj;
			update_param(param, e);
			COLOR = 0x00000000;
			DIST = DIST_MAX;
			while (elem)
			{
				obj = (t_object *)elem->content;
				if (!ft_strcmp(obj->type, "sphere"))
					sphere(param, obj);
				elem = elem->next;
				img_put_pixel(e, X, Y, COLOR);
			}
			//plane(param, &a);
		}
	}
	pthread_exit(0);
}
