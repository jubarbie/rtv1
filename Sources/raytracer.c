/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 15:41:19 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/23 19:52:52 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	update_param(t_param *param, t_env *e)
{
	RAY_POS = fill_vector(CAM_POS.x, CAM_POS.y, CAM_POS.z);
	GAP_X = VW_WIDTH / (double)WIN_WIDTH;
	GAP_Y = VW_HEIGHT / (double)WIN_HEIGHT;	
	RAY_DIR = unit_vector(add_vectors(VW_UP_LEFT, sub_vectors(time_vector(CAM_RIGHT,
								GAP_X * X), time_vector(CAM_UP, GAP_Y * Y))));
	VW_UP_LEFT = add_vectors(CAM_POS, sub_vectors(add_vectors(
				time_vector(CAM_DIR, VW_DIST), time_vector(
				CAM_UP, VW_HEIGHT / 2.0)), time_vector(CAM_RIGHT, VW_WIDTH / 2.0)));
}

void	*raytracer(void *arg)
{
	t_env	*e;
	t_param	*param;
	double	a;

	a = 0;
	param = (t_param *)arg;
	e = ENV;
	Y = TH * (WIN_HEIGHT / NB_TH) - 1;
	while (++Y < (TH + 1) * WIN_HEIGHT / NB_TH)
	{
		X = -1;
		while (++X < WIN_WIDTH)
		{
			COLOR = 0x00000000;
			update_param(param, e);
			sphere(param, &a);
			img_put_pixel(e, X, Y, COLOR);
		}
	}
	pthread_exit(0);
}
