/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/01 18:41:03 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cylinder(t_object *obj, t_ray *ray)
{
	float	r;
	t_v3d	n;
	t_v3d	o;
	t_v3d	dp;
	float	a;
	float	b;
	float	c;

	float	det;
	float	s1;
	float	s2;

	r = obj->param[0];
	n = unit_v3d(v3d(obj->param[1], obj->param[2], obj->param[3]));
	o = obj->pos;

	dp = sub_v3d(ray->pos, obj->pos);
	a = dot_v3d((sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)))), 
			sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n))));
	b = 2 * (dot_v3d((sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)))), 
				sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n)))));
	c = dot_v3d((sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n)))), 
			(sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n))))) - pow(r, 2.0);

	det = b * b - 4.0 * a * c;
	if (det >= 0)
	{
		s1 = (-b + sqrt(det)) / 2.0 * a;
		s2 = (-b - sqrt(det)) / 2.0 * a;
		if (s2 < s1 && s2 > 0)
			s1 = s2;
		//s = fmin(fabs(s2), fabs(s1));
		if (s1 > 0 && s1 < ray->dist)
		{
			ray->det = det;
			ray->obj = obj;
			ray->dist = s1;
			ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, s1));
			ray->norm = add_v3d(v3d(obj->pos.x, ray->inter.y, obj->pos.z), smul_v3d(unit_v3d(sub_v3d(ray->inter, v3d(obj->pos.x, ray->inter.y, obj->pos.z))), r));
		}
	}
}
