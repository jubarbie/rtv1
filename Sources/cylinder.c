/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/10 16:51:43 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		set_cylinder_norm(t_object *obj, t_ray *ray)
{
	double	l;
	t_v3d	n;

	n = unit_v3d(sub_v3d(v3d(obj->param[1], obj->param[2], obj->param[3]),
																	obj->pos));
	ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, ray->dist));
	l = length_v3d(sub_v3d(ray->inter, obj->pos));
	l = sqrt(pow(l, 2.0) - pow(obj->param[0], 2.0));
	ray->norm = unit_v3d(sub_v3d(ray->inter, add_v3d(obj->pos,
															smul_v3d(n, l))));
}

static void		find_dist(t_object *obj, t_ray *ray, double *sol)
{
	int		i;
	double	max;
	int		index;
	t_v3d	p2;

	i = -1;
	max = ray->dist;
	p2 = v3d(obj->param[1], obj->param[2], obj->param[3]);
	while (++i < 4)
		if (sol[i] > 0 && sol[i] < max)
		{
			index = i;
			max = sol[i];
		}
	if (max < ray->dist)
	{
		ray->dist = max;
		ray->obj = obj;
		if (index == 0 || index == 1)
			set_cylinder_norm(obj, ray);
		else if (index == 2)
			ray->norm = unit_v3d(sub_v3d(p2, obj->pos));
		else if (index == 3)
			ray->norm = unit_v3d(sub_v3d(obj->pos, p2));
	}
}

static void		find_solutions(t_object *obj, t_ray *ray, t_v3d abc)
{
	t_v3d	p2;
	t_v3d	tmp;
	t_v3d	n;
	double	det;
	double	sol[4];

	p2 = v3d(obj->param[1], obj->param[2], obj->param[3]);
	n = unit_v3d(sub_v3d(p2, obj->pos));
	if ((det = ft_solve_quadratic(abc.x, abc.y, abc.z, &sol[0], &sol[1])) >= 0)
	{
		sol[2] = -1;
		while (++sol[2] < 2)
			if (sol[(int)sol[2]] >= 0)
			{
				tmp = add_v3d(ray->pos, smul_v3d(ray->dir, sol[(int)sol[2]]));
				if (!(dot_v3d(n, sub_v3d(tmp, obj->pos)) > 0 &&
											dot_v3d(n, sub_v3d(tmp, p2)) < 0))
					sol[(int)sol[2]] = -1;
			}
		sol[2] = caps(ray, obj->param[0], n, p2);
		sol[3] = caps(ray, obj->param[0], smul_v3d(n, -1), obj->pos);
		find_dist(obj, ray, sol);
	}
}

void			cylinder(t_object *obj, t_ray *ray)
{
	double	r;
	t_v3d	n;
	t_v3d	p1;
	t_v3d	p2;
	t_v3d	dp;

	r = obj->param[0];
	p1 = obj->pos;
	p2 = v3d(obj->param[1], obj->param[2], obj->param[3]);
	n = unit_v3d(sub_v3d(p2, p1));
	dp = sub_v3d(ray->pos, obj->pos);
	p1 = sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)));
	p2.x = dot_v3d(p1, p1);
	p2.y = 2 * dot_v3d((sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)))),
			sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n))));
	p1 = sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n)));
	p2.z = dot_v3d(p1, p1) - pow(r, 2.0);
	find_solutions(obj, ray, p2);
}
