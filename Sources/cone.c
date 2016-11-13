/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 09:11:28 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/10 10:46:15 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	find_inter(t_object *obj, t_ray *ray, t_v3d q, float r)
{
	float	t0;
	float	t1;

	t0 = (-q.y + sqrt(r)) / 2.0 * q.x;
	t1 = (-q.y - sqrt(r)) / 2.0 * q.x;
	t0 = fmin(t0, t1);
	if (t0 < ray->dist)
	{
		ray->obj = obj;
		ray->dist = t0;
		ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t0));
		ray->norm = unit_v3d(sub_v3d(ray->inter, obj->pos));
	}
}

void		cone(t_object *obj, t_ray *ray)
{
	t_v3d	o;
	t_v3d	q;
	float	r;

	o = v3d(obj->pos.x, obj->pos.y, obj->pos.z);
	q.x = ray->dir.y * ray->dir.y + ray->dir.z * ray->dir.z -
			ray->dir.x * ray->dir.x;
	q.y = 2.0 * (ray->dir.y * (ray->pos.y - o.y) +
			ray->dir.z * (ray->pos.z - o.z) - ray->dir.x * (ray->pos.x - o.x));
	q.z = (pow(ray->pos.y - o.y, 2.0) + pow(ray->pos.z - o.z, 2.0) -
			pow(ray->pos.x - o.x, 2.0));
	r = q.y * q.y - 4.0 * q.x * q.z;
	if (r >= 0.0)
		find_inter(obj, ray, q, r);
}