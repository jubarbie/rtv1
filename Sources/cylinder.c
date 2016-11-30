/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/30 18:30:45 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	low_caps(t_object *obj, t_ray *ray, t_v3d t, t_v3d y, t_v3d r)
{
	float	d;

	d = t.x + (t.y - t.x) * (y.x - r.y) / (y.x - y.y);
	if (d > 0.0)
	{
		ray->obj = obj;
		ray->dist = d;
		ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, d));
		ray->norm = v3d(0, 1, 0);
	}
}

static void	up_caps(t_object *obj, t_ray *ray, t_v3d t, t_v3d y, t_v3d r)
{
	float	d;

	d = t.x + (t.y - t.x) * (y.x + r.z) / (y.x - y.y);
	if (d > 0.0)
	{
		ray->obj = obj;
		ray->dist = d;
		ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, d));
		ray->norm = unit_v3d(v3d(0, -1, 0));
	}
}

static void	find_inter(t_object *obj, t_ray *ray, t_v3d t, t_v3d r)
{
	t_v3d	y;

	y.x = ray->pos.y + t.x * ray->dir.y;
	y.y = ray->pos.y + t.y * ray->dir.y;
	if (y.x < r.y)
	{
		if (y.y >= r.y)
			up_caps(obj, ray, t, y, r);
	}
	else if (y.x >= r.y && y.x <= r.z)
	{
		if (t.x > 0.0)
		{
			ray->obj = obj;
			ray->dist = t.x;
			ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t.x));
			ray->norm = sub_v3d(ray->inter, v3d(obj->pos.x, ray->inter.y, obj->pos.z));
		}
	}
	else if (y.x > r.z)
	{
		if (y.y <= r.z)
			low_caps(obj, ray, t, y, r);
	}
}

void		cylinder(t_object *obj, t_ray *ray)
{
	t_v3d	n;
	t_v3d	q;
	t_v3d	r;
	t_v3d	t;

	r = v3d(obj->param[0], obj->param[1], obj->param[2]);
	n = obj->pos;
	q.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	q.y = 2 * (ray->dir.x * (ray->pos.x - n.x) + ray->dir.z * (ray->pos.z - n.z));
	q.z = pow(ray->pos.x - n.x, 2.0) + pow(ray->pos.z - n.z, 2.0) - r.x * r.x;
	r.x = q.y * q.y - 4.0 * q.x * q.z;
	if (r.x >= 0.0)
	{
		t.x = (-q.y + sqrt(r.x)) / 2.0 * q.x;
		t.y = (-q.y - sqrt(r.x)) / 2.0 * q.x;
		if (t.x > t.y)
		{
			r.x = t.x;
			t.x = t.y;
			t.y = r.x;
		}
		find_inter(obj, ray, t, r);
	}
}
