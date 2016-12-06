/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/06 13:05:39 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cylinder(t_object *obj, t_ray *ray)
{
	double	r;
	t_v3d	n;
	t_v3d	p1;
	t_v3d	p2;
	t_v3d	dp;
	t_v3d	tmp;
	t_v3d	abc;
	double	det;
	double	t0;
	double	t1;
	double	tp0;
	double	tp1;
	double	tp2;
	double	tp3;

	r = obj->param[0];
	p1 = v3d(obj->pos.x, obj->pos.y, obj->pos.z);
	p2 = v3d(obj->param[1], obj->param[2], obj->param[3]);
	n = unit_v3d(sub_v3d(p2, p1));

	dp = sub_v3d(ray->pos, obj->pos);
	tmp = sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)));
	abc.x = dot_v3d(tmp, tmp);
	abc.y = 2 * dot_v3d((sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)))), 
				sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n))));
	tmp = sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n)));
	abc.z = dot_v3d(tmp, tmp) - pow(r, 2.0);
	if ((det = ft_solve_quadratic(abc.x, abc.y, abc.z, &t0, &t1)) >= 0)
	{
		tp0 = -1;
		tp1 = -1;
		tp2 = -1;
		tp3 = -1;
		if (t0 >= 0)
		{
			tmp = add_v3d(ray->pos, smul_v3d(ray->dir, t0));
			if (dot_v3d(n, sub_v3d(tmp, p1)) > 0 && dot_v3d(n, sub_v3d(tmp, p2)) < 0)
				tp0 = t0;
		}
		if (t1 >= 0)
		{
			tmp = add_v3d(ray->pos, smul_v3d(ray->dir, t1));
			if (dot_v3d(n, sub_v3d(tmp, p1)) > 0 && dot_v3d(n, sub_v3d(tmp, p2)) < 0)
					tp1 = t1;
		}
		det = dot_v3d(n, ray->dir);
		if (det < 0.0000001 || det > 0.0000001)
		{
			tmp = sub_v3d(p2, ray->pos);
			tp2 = dot_v3d(tmp, n) / det;
			if (tp2 > 0)
			{
				tmp = add_v3d(ray->pos, smul_v3d(ray->dir, tp2));
				if (dot_v3d(sub_v3d(tmp, p2), sub_v3d(tmp, p2)) >= r * r)
					tp2 = -1;
			}
		}
		n = unit_v3d(sub_v3d(p1, p2));
		det = dot_v3d(n, ray->dir);
		if (det < 0.0000001 || det > 0.0000001)
		{
			tmp = sub_v3d(p1, ray->pos);
			tp3 = dot_v3d(tmp, n) / det;
			if (tp3 > 0)
			{
				tmp = add_v3d(ray->pos, smul_v3d(ray->dir, tp3));
				if (dot_v3d(sub_v3d(tmp, p1), sub_v3d(tmp, p1)) >= r * r)
					tp3 = -1;
			}
		}
		if ((tp2 < tp0 && tp2 > 0) || (tp2 > tp0 && tp0 < 0))
			tp0 = tp2;
		if ((tp3 < tp1 && tp3 > 0) || (tp3 > tp1 && tp1 < 0))
			tp1 = tp3;
		find_dist(obj, ray, tp0, tp1);	
	}
}

void		cylinder_norm(t_ray *ray)
{
	ray->norm = sub_v3d(ray->inter, v3d(ray->obj->pos.x, ray->inter.y, ray->obj->pos.z));
}

