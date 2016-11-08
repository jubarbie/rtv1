/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 19:55:56 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/08 13:03:59 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plane(t_object *obj, t_ray *ray)
{
	t_v3d	n;
	t_v3d	q;
	double		t0;
	double		t1;
	double		t;
	double		det;
	double		y0;
	double		y1;

	n = v3d(obj->param[0], obj->param[1], obj->param[2]);
	q.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	q.y = 2 * ray->dir.x * ray->pos.x + 2 * ray->dir.z * ray->pos.z;
	q.z = ray->pos.x * ray->pos.x + ray->pos.z * ray->pos.z - 1;
	det = q.y * q.y - 4.0 * q.x * q.z;
	if (det >= 0.0)
	{
		t0 = (-q.y + sqrt(det)) / 2.0 * q.x;
		t1 = (-q.y - sqrt(det)) / 2.0 * q.x;
		t = fmin(t0, t1);
		y0 = ray->pos.y + t1 * ray->dir.y;
		y1 = ray->pos.y + t0 * ray->dir.y;
		if (t < ray->dist && y0 > -1 && y1 < 1)
		{
			ray->obj = obj;
			ray->dist = t0;
			ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t0));
		}
	}

}
