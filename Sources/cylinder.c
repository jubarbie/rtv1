/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/10 09:03:49 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	low_caps(t_object *obj, t_ray *ray, t_v3d t, t_v3d y)
{
	float	d;

	d = t.x + (t.y - t.x) * (y.x - 1.0) / (y.x - y.y);
	if (d > 0.0)
	{
		ray->obj = obj;
		ray->dist = d;
		ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, d));
		ray->norm = v3d(0, 1, 0);
	}
}

static void	up_caps(t_object *obj, t_ray *ray, t_v3d t, t_v3d y)
{
	float	d;

	d = t.x + (t.y - t.x) * (y.x + 1.0) / (y.x - y.y);
	if (d > 0.0)
	{
		ray->obj = obj;
		ray->dist = d;
		ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, d));
		ray->norm = v3d(0, -1, 0);
	}
}

static void	find_inter(t_object *obj, t_ray *ray, t_v3d t)
{
	t_v3d	y;

	y.x = ray->pos.y + t.x * ray->dir.y;
	y.y = ray->pos.y + t.y * ray->dir.y;
	if (y.x < -1.0)
	{
		if (y.y >= -1.0)
			up_caps(obj, ray, t, y);
	}
	else if (y.x >= -1.0 && y.x <= 1.0)
	{
		if (t.x > 0.0)
		{
			ray->obj = obj;
			ray->dist = t.x;
			ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t.x));
			ray->norm = v3d(ray->inter.x, 0, ray->inter.z);
		}
	}
	else if (y.x > 1.0)
	{
		if (y.y <= 1.0)
			low_caps(obj, ray, t, y);
	}
}

void		cylinder(t_object *obj, t_ray *ray)
{
	t_v3d	n;
	t_v3d	q;
	float	r;
	t_v3d	t;

	r = obj->param[0];
	n = unit_v3d(obj->pos);
	q.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	q.y = 2 * (ray->dir.x * ray->pos.x + ray->dir.z * ray->pos.z);
	q.z = ray->pos.x * ray->pos.x + ray->pos.z * ray->pos.z - r * r;
	r = q.y * q.y - 4.0 * q.x * q.z;
	if (r >= 0.0)
	{
		t.x = (-q.y + sqrt(r)) / 2.0 * q.x;
		t.y = (-q.y - sqrt(r)) / 2.0 * q.x;
		if (t.x > t.y)
		{
			r = t.x;
			t.x = t.y;
			t.y = r;
		}
		find_inter(obj, ray, t);
	}
}
