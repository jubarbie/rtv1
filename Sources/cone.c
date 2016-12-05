/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/03 17:11:08 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cone(t_object *obj, t_ray *ray)
{
	double	angle;
	t_v3d	n;
	t_v3d	dp;
	t_v3d	tmp;
	double	a;
	double	b;
	double	c;
	double	det;
	double	s1;
	double	s2;
	double	sina;
	double	cosa;

	angle = obj->param[0];
	n = unit_v3d(v3d(obj->param[1], obj->param[2], obj->param[3]));

	dp = sub_v3d(ray->pos, obj->pos);
	sina = pow(sin(angle), 2.0);
	cosa = pow(cos(angle), 2.0);
	tmp = sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)));
	a = cosa * dot_v3d(tmp, tmp) - sina * dot_v3d(ray->dir, n) * dot_v3d(ray->dir, n);

	det = 2 * cosa * dot_v3d(sub_v3d(ray->dir, smul_v3d(n, dot_v3d(n, ray->dir))), sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n))));
	b = det - 2 * sina * dot_v3d(ray->dir, n) * dot_v3d(dp, n);
	tmp = sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n)));
	c = cosa * dot_v3d(tmp, tmp) - sina * dot_v3d(dp, n) * dot_v3d(dp, n);

	det = pow(b, 2.0) - 4.0 * a * c;
	if (det > 0)
	{
		s1 = (-b + sqrt(det)) / 2.0 * a;
		s2 = (-b - sqrt(det)) / 2.0 * a;
		if ((s2 < s1 && s2 > 0) || (s2 > s1 && s1 < 0))
			s1 = s2;
		if (s1 > 0 && s1 < ray->dist)
		{
			ray->det = det;
			ray->obj = obj;
			ray->dist = s1;
			ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, s1));
			ray->norm = sub_v3d(ray->inter, v3d(obj->pos.x, ray->inter.y, obj->pos.z));
		}
	}
}
