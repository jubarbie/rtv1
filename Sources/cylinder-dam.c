/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/07 19:06:43 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	cylindre(t_data *data, t_ray ray, t_form *form)
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
	n = unit_v3d(ft_sub(p2, p1));

	dp = ft_sub(ray.pos, obj->pos);
	tmp = ft_sub(ray.vec, smul_v3d(n, ft_dot(ray.vec, n)));
	abc.x = ft_dot(tmp, tmp);
	abc.y = 2 * ft_dot((ft_sub(ray.vec, smul_v3d(n, ft_dot(ray.vec, n)))), 
				ft_sub(dp, smul_v3d(n, ft_dot(dp, n))));
	tmp = ft_sub(dp, smul_v3d(n, ft_dot(dp, n)));
	abc.z = ft_dot(tmp, tmp) - pow(r, 2.0);
	if ((det = ft_solve_quadratic(abc.x, abc.y, abc.z, &t0, &t1)) >= 0)
	{
		tp0 = -1;
		tp1 = -1;
		tp2 = -1;
		tp3 = -1;
		if (t0 >= 0)
		{
			tmp = add_v3d(ray.pos, smul_v3d(ray.vec, t0));
			if (ft_dot(n, ft_sub(tmp, p1)) > 0 && ft_dot(n, ft_sub(tmp, p2)) < 0)
				tp0 = t0;
		}
		if (t1 >= 0)
		{
			tmp = add_v3d(ray.pos, smul_v3d(ray.vec, t1));
			if (ft_dot(n, ft_sub(tmp, p1)) > 0 && ft_dot(n, ft_sub(tmp, p2)) < 0)
					tp1 = t1;
		}
		det = ft_dot(n, ray.vec);
		if (det < 0.0000001 || det > 0.0000001)
		{
			tmp = ft_sub(p2, ray.pos);
			tp2 = ft_dot(tmp, n) / det;
			if (tp2 > 0)
			{
				tmp = add_v3d(ray.pos, smul_v3d(ray.vec, tp2));
				if (ft_dot(ft_sub(tmp, p2), ft_sub(tmp, p2)) >= r * r)
					tp2 = -1;
			}
		}
		n = unit_v3d(ft_sub(p1, p2));
		det = ft_dot(n, ray.vec);
		if (det < 0.0000001 || det > 0.0000001)
		{
			tmp = ft_sub(p1, ray.pos);
			tp3 = ft_dot(tmp, n) / det;
			if (tp3 > 0)
			{
				tmp = add_v3d(ray.pos, smul_v3d(ray.vec, tp3));
				if (ft_dot(ft_sub(tmp, p1), ft_sub(tmp, p1)) >= r * r)
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
	ray->norm = ft_sub(ray->inter, v3d(ray->obj->pos.x, ray->inter.y, ray->obj->pos.z));
}

