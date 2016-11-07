/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/03 17:29:09 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	cylinder(t_object *obj, t_ray *ray)
{
	t_vector	n;
	t_vector	q;
	double		t0;
	double		t1;
	double		t;
	double		det;
	double		y0;
	double		y1;
	double		r;

	r = obj->param[0];
	n = fill_vector(obj->param[0], obj->param[1], obj->param[2]);
	q.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	q.y = 2 * (ray->dir.x * ray->pos.x + ray->dir.z * ray->pos.z);
	q.z = ray->pos.x * ray->pos.x + ray->pos.z * ray->pos.z - r * r;
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
		//t = fmin(t0, t1);
		y0 = ray->pos.y + t0 * ray->dir.y;
		y1 = ray->pos.y + t1 * ray->dir.y;
		if (y0 < -1)
		{
			if (y1 >= -1)
			{
				t = t0 + (t1 - t0) * (y0 + 1) / (y0 - y1);
				if (t > 0)
				{
					ray->obj = obj;
					ray->dist = t;
					ray->inter = add_vectors(ray->pos, time_vector(ray->dir, t));
				}
			}
		}
		else if (y0 >= -1 && y0 <= 1)
		{
			if (t0 > 0)
			{
				ray->obj = obj;
				ray->dist = t0;
				ray->inter = add_vectors(ray->pos, time_vector(ray->dir, t0));
			}
		}
		else if (y0 > 1)
		{
			if (y1 <= 1)
			{
				t = t0 + (t1 - t0) * (y0 - 1) / (y0 - y1);
				if (t > 0)
				{
					ray->obj = obj;
					ray->dist = t;
					ray->inter = add_vectors(ray->pos, time_vector(ray->dir, t));
				}
			}
		}
		/*if (t0 < ray->dist && y0 > -1 && y0 < 1 && t0 > 0)
		{
			ray->obj = obj;
			ray->dist = t0;
			ray->inter = add_vectors(ray->pos, time_vector(ray->dir, t0));
		}*/
	}
}
