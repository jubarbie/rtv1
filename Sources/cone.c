/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/03 16:41:28 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cone(t_object *obj, t_ray *ray)
{
	float	angle;
	t_v3d	n;
	t_v3d	dp;
	t_v3d	tmp;
	float	a;
	float	b;
	float	c;
	float	det;
	float	s1;
	float	s2;
	float	sina;
	float	cosa;

	angle = obj->param[0];
	n = unit_v3d(v3d(obj->param[1], obj->param[2], obj->param[3]));

	dp = sub_v3d(ray->pos, obj->pos);
	sina = (float)sin(angle);
	cosa = (float)cos(angle);
	cosa *= cosa;
	sina *= sina;
	tmp = sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)));
	a = cosa * dot_v3d(tmp, tmp) - sina * dot_v3d(ray->dir, n) * dot_v3d(ray->dir, n);

	det = 2 * cosa * dot_v3d(sub_v3d(ray->dir, smul_v3d(n, dot_v3d(n, ray->dir))), sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n))));
	b = det - 2 * sina * dot_v3d(ray->dir, n) * dot_v3d(dp, n);
	tmp = sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n)));
	c = cosa * dot_v3d(tmp, tmp) - sina * dot_v3d(dp, n) * dot_v3d(dp, n);

	det = b * b - 4.0 * a * c;
	if (det > 0.0000001)
	{
		s1 = (-b + (float)sqrt(det)) / 2.0 * a;
		s2 = (-b - (float)sqrt(det)) / 2.0 * a;
		if (s2 < s1 && s2 > 0.0000001)
			s1 = s2;
		if (s1 > 0.0000001 && s1 < ray->dist)
		{
			ray->det = det;
			ray->obj = obj;
			ray->dist = s1;
			ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, s1));
			ray->norm = sub_v3d(ray->inter, v3d(obj->pos.x, ray->inter.y, obj->pos.z));
		}
	}
}
