/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 09:11:28 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/09 17:32:28 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	find_dist(t_object *obj, t_ray *ray, double t0, double t1)
{
	if ((t1 < t0 && t1 > 0) || (t1 > t0 && t0 < 0))
		t0 = t1;
	if (t0 > 0 && t0 < ray->dist)
	{
		ray->obj = obj;
		ray->dist = t0;
		ray->norm = unit_v3d(sub_v3d(ray->inter, ray->obj->pos));
	}
}

void		sphere(t_object *obj, t_ray *ray)
{
	t_v3d	o;
	t_v3d	abc;
	double	r;
	double	t1;
	double	t0;

	o = v3d(obj->pos.x, obj->pos.y, obj->pos.z);
	r = obj->param[0];
	abc.x = ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y +
			ray->dir.z * ray->dir.z;
	abc.y = 2.0 * (ray->dir.x * (ray->pos.x - o.x) +
			ray->dir.y * (ray->pos.y - o.y) + ray->dir.z * (ray->pos.z - o.z));
	abc.z = (pow(ray->pos.x - o.x, 2.0) + pow(ray->pos.y - o.y, 2.0) +
			pow(ray->pos.z - o.z, 2.0)) - r * r;
	if ((r = ft_solve_quadratic(abc.x, abc.y, abc.z, &t0, &t1)) >= 0)
		find_dist(obj, ray, t0, t1);
}
