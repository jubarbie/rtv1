/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/25 19:23:41 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	get_color(t_param *param, t_object *obj, t_vector q, double det)
{
	t_hsv	hsv;
	double	t1;
	double	t2;

	t1 = (-q.y + sqrt(det)) / 2.0 * q.x;
	t2 = (-q.y - sqrt(det)) / 2.0 * q.x;
	t1 = fmin(fabs(t1), fabs(t2));
	if (t1 < DIST)
	{
		OBJ = obj;
		DIST = t1;
		rgb_to_hsv(obj->color, &hsv.h, &hsv.s, &hsv.v);
		RAY = add_vectors(RAY_POS, time_vector(RAY_DIR, t1));
		COLOR = hsv_to_rgb(hsv.h, hsv.s, det * 2 / obj->param[0]);
	}
}

void		sphere(t_param *param, t_object *obj)
{
	t_vector	o;
	t_vector	q;
	double		r;

	o = fill_vector(obj->pos.x, obj->pos.y, obj->pos.z);
	r = obj->param[0];
	q.x = RAY_DIR.x * RAY_DIR.x + RAY_DIR.y * RAY_DIR.y + RAY_DIR.z * RAY_DIR.z;
	q.y = 2.0 * (RAY_DIR.x * (RAY_POS.x - o.x) + RAY_DIR.y * (RAY_POS.y - o.y) +
			RAY_DIR.z * (RAY_POS.z - o.z));
	q.z = (pow(RAY_POS.x - o.x, 2.0) + pow(RAY_POS.y - o.y, 2.0) +
			pow(RAY_POS.z - o.z, 2.0)) - r * r;
	r = q.y * q.y - 4.0 * q.x * q.z;
	if (r >= 0)
		get_color(param, obj, q, r);
}
