/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 19:55:56 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/24 12:19:24 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plane(t_param *param, double *arg)
{
	double a = 0.0;
	double b = 1.0;
	double c = 0.0;
	double d = 0.0;
	t_hsv	col;
	double t;

	*arg = 0;	
	t = (a * (RAY_POS.x - 0)) + (b * (RAY_POS.y - 0)) + (c * (RAY_POS.z - 0)) + d;
	t /= a * RAY_DIR.x + b * RAY_DIR.y + c * RAY_DIR.z;
	t *= -1;
	printf("t: %lf\n", t);	
	if (t < 0)
	{
		COLOR = 0x0000FF00;
		rgb_to_hsv(COLOR, &col.h, &col.s, &col.v);
		COLOR = hsv_to_rgb(col.h, col.s, col.v - fabs(t) / 10000);
	}

}
