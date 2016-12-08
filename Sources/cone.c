/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/08 15:39:50 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cone(t_object *obj, t_ray *ray)
{
	double	angle;
	t_v3d	n;
	t_v3d	dp;
	t_v3d	tmp;
	t_v3d	abc;
	double	det;
	double	t0;
	double	t1;
	double	sina;
	double	cosa;

	angle = obj->param[0];
	n = unit_v3d(v3d(obj->param[1], obj->param[2], obj->param[3]));

	dp = sub_v3d(ray->pos, obj->pos);
	sina = pow(sin(angle), 2.0);
	cosa = pow(cos(angle), 2.0);
	tmp = sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)));
	abc.x = cosa * dot_v3d(tmp, tmp) - sina * dot_v3d(n, ray->dir) * dot_v3d(n, ray->dir);
	det = 2 * cosa * dot_v3d(sub_v3d(ray->dir, smul_v3d(n, dot_v3d(n, ray->dir))), sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n))));
	abc.y = det - 2 * sina * dot_v3d(n, ray->dir) * dot_v3d(dp, n);
	tmp = sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n)));
	abc.z = cosa * dot_v3d(tmp, tmp) - sina * dot_v3d(dp, n) * dot_v3d(dp, n);
	if ((det = ft_solve_quadratic(abc.x, abc.y, abc.z, &t0, &t1)) >= 0)
	find_dist(obj, ray, t0, t1);
}

void	cone_norm(t_ray *ray)
{
	ray->norm = sub_v3d(ray->inter, v3d(ray->obj->pos.x, ray->inter.y, ray->obj->pos.z));
}
