/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/09 17:25:50 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	cylinder(t_object *obj, t_ray *ray)
{
	t_v3d	n;
	t_v3d	q;
	float	t0;
	float	t1;
	float	t;
	float	det;
	float	y0;
	float	y1;
	float	r;

	r = obj->param[0];
	n = unit_v3d(obj->pos);
	q.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	q.y = 2 * (ray->dir.x * ray->pos.x + ray->dir.z * ray->pos.z);
	q.z = ray->pos.x * ray->pos.x + ray->pos.z * ray->pos.z - 1;
	det = q.y * q.y - 4.0 * q.x * q.z;
	if (det >= 0.0)
	{
		t0 = (-q.y + sqrt(det)) / 2.0 * q.x;
		t1 = (-q.y - sqrt(det)) / 2.0 * q.x;
		if (t0 > t1)
		{
			t = t0;
			t0 = t1;
			t1 = t;
		}
		y0 = ray->pos.y + t0 * ray->dir.y;
		y1 = ray->pos.y + t1 * ray->dir.y;
		if (y0 < -1.0)
		{
			if (y1 >= -1.0)
			{
				t = t0 + (t1 - t0) * (y0 + 1.0) / (y0 - y1);
				if (t > 0.0)
				{
					ray->obj = obj;
					ray->dist = t;
					ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t));
					ray->norm = v3d(0, -1, 0);
				}
			}
		}
		else if (y0 >= -1.0 && y0 <= 1.0)
		{
			if (t0 > 0.0)
			{
				ray->obj = obj;
				ray->dist = t0;
				ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t0));
				ray->norm = v3d(ray->inter.x, 0, ray->inter.z);
			}
		}
		else if (y0 > 1.0)
		{
			if (y1 <= 1.0)
			{
				t = t0 + (t1 - t0) * (y0 - 1.0) / (y0 - y1);
				if (t > 0.0)
				{
					ray->obj = obj;
					ray->dist = t;
					ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t));
					ray->norm = v3d(0, 1, 0);
				}
			}
		}	
	}
}
