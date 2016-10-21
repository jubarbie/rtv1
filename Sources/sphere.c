/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/21 20:24:03 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	sphere(t_param *param, double *arg)
{
	double	a;
	double	b;
	double	c;
	t_vector	dir;
	t_vector	o;
	double		r;
	double		det;

	*arg = 0;	
	dir = unit_vector(RAY_DIR);
	o = fill_vector(0, 0, 0);
	r = 1.2;
	a = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
	b = 2 * (dir.x * (RAY_POS.x - o.x) + RAY_DIR.y * (RAY_POS.y - o.y) + RAY_DIR.z * (RAY_POS.z - o.z));
	c = (pow(RAY_POS.x - o.x, 2.0) + pow(RAY_POS.y - o.y, 2.0) + pow(RAY_POS.z - o.z, 2.0)) - r * r;
	det = b * b - 4 * a * c;
	//printf("det: %lf\n", det);
	if (det >= 0)
		COLOR = 0x0000FF00;
}
