/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/24 14:35:21 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	sphere(t_param *param, t_object *obj)
{
	t_vector	o;
	t_vector	q;
	//double		b;
	//double		c;
	double		r;
	double		det;
	double		t1;
	double		t2;
	t_hsv		hsv;

	o = fill_vector(obj->pos.x, obj->pos.y, obj->pos.z);
	r = obj->param[1];
	q.x = RAY_DIR.x * RAY_DIR.x + RAY_DIR.y * RAY_DIR.y + RAY_DIR.z * RAY_DIR.z;
	q.y = 2.0 * (RAY_DIR.x * (RAY_POS.x - o.x) + RAY_DIR.y * (RAY_POS.y - o.y) +
			RAY_DIR.z * (RAY_POS.z - o.z));
	q.z = (pow(RAY_POS.x - o.x, 2.0) + pow(RAY_POS.y - o.y, 2.0) +
			pow(RAY_POS.z - o.z, 2.0)) - r * r;
	det = q.y * q.y - 4.0 * q.x * q.z;
	if (det >= 0)
	{
		t1 = (-q.y + sqrt(det)) / 2.0 * q.x;
		t2 = (-q.y - sqrt(det)) / 2.0 * q.x;
		t1 = fmin(t1, t2);
		//RAY = add_vectors(RAY_POS, time_vector(RAY_DIR, t));
		//t = norm_vector(RAY);
		rgb_to_hsv(obj->color, &hsv.h, &hsv.s, &hsv.v);
		COLOR = hsv_to_rgb(hsv.h, hsv.s, det * 20);
	}
}
