/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/23 19:52:50 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	sphere(t_param *param, double *arg)
{
	double	a;
	double	b;
	double	c;
	t_vector	o;
	double		r;
	double		det;
	double		t1;
	double		t2;
	double		t;
	int			h;
	double		s;
	double		v;

	*arg = 0;	
	o = fill_vector(0, 0, 0);
	r = 10.0;
	a = RAY_DIR.x * RAY_DIR.x + RAY_DIR.y * RAY_DIR.y + RAY_DIR.z * RAY_DIR.z;
	b = 2.0 * (RAY_DIR.x * (RAY_POS.x - o.x) + RAY_DIR.y * (RAY_POS.y - o.y) + RAY_DIR.z * (RAY_POS.z - o.z));
	c = (pow(RAY_POS.x - o.x, 2.0) + pow(RAY_POS.y - o.y, 2.0) + pow(RAY_POS.z - o.z, 2.0)) - r * r;
	det = b * b - 4.0 * a * c;
	//printf("det: %lf\n", det);
	if (det >= 0)
	{
		t1 = (-b + sqrt(det)) / 2.0 * a;
		t2 = (-b - sqrt(det)) / 2.0 * a;
		t = fmin(t1, t2);
		RAY = add_vectors(RAY_POS, time_vector(RAY_DIR, t));
		t = norm_vector(RAY);
		//printf("t: %lf\n", t);
		COLOR = (det <= 10 && det >= -10) ? 0x00FF0000: 0x0000FF00;
		rgb_to_hsv(COLOR, &h, &s, &v);
		COLOR = hsv_to_rgb(h + det / r, s, v - r * 10 / det);
		//printf("%d\n", COLOR);
	}
}
