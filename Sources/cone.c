/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/09 18:41:21 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_cone_norm(t_object *obj, t_ray *ray)
{
	double	l;
	t_v3d	n;

	n = unit_v3d(v3d(obj->param[1], obj->param[2], obj->param[3]));
	ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, ray->dist));
	l = length_v3d(sub_v3d(ray->inter, obj->pos));
	l /= cos(obj->param[0]);
	if (dot_v3d(n, sub_v3d(ray->inter, obj->pos)) < 0)
		l *= -1;
	ray->norm = unit_v3d(sub_v3d(ray->inter,
										add_v3d(obj->pos, smul_v3d(n, l))));
}

static void	find_dist(t_object *obj, t_ray *ray, double t0, double t1)
{
	if ((t1 < t0 && t1 > 0) || (t1 > t0 && t0 < 0))
		t0 = t1;
	if (t0 > 0 && t0 < ray->dist)
	{
		ray->obj = obj;
		ray->dist = t0;
		set_cone_norm(obj, ray);
	}
}

void		cone(t_object *obj, t_ray *ray)
{
	t_v3d	p[3];
	t_v3d	abc;
	double	sol[2];
	double	sina;
	double	cosa;

	p[0] = unit_v3d(v3d(obj->param[1], obj->param[2], obj->param[3]));
	p[1] = sub_v3d(ray->pos, obj->pos);
	sina = pow(sin(obj->param[0]), 2.0);
	cosa = pow(cos(obj->param[0]), 2.0);
	p[2] = sub_v3d(ray->dir, smul_v3d(p[0], dot_v3d(ray->dir, p[0])));
	abc.x = cosa * dot_v3d(p[2], p[2]) - sina * dot_v3d(p[0], ray->dir) *
														dot_v3d(p[0], ray->dir);
	sol[0] = 2 * cosa * dot_v3d(sub_v3d(ray->dir, smul_v3d(p[0], dot_v3d(p[0],
			ray->dir))), sub_v3d(p[1], smul_v3d(p[0], dot_v3d(p[1], p[0]))));
	abc.y = sol[0] - 2 * sina * dot_v3d(p[0], ray->dir) * dot_v3d(p[1], p[0]);
	p[2] = sub_v3d(p[1], smul_v3d(p[0], dot_v3d(p[1], p[0])));
	abc.z = cosa * dot_v3d(p[2], p[2]) - sina *
									dot_v3d(p[1], p[0]) * dot_v3d(p[1], p[0]);
	if (ft_solve_quadratic(abc.x, abc.y, abc.z, &sol[0], &sol[1]) >= 0)
		find_dist(obj, ray, sol[0], sol[1]);
}
