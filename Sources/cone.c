/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/12 19:35:01 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_cone_norm(t_ray *ray, t_v3d *p, double *a)
{
	double	l;
	t_v3d	n;
	t_v3d	pos;

	n = p[0];
	pos = p[5];
	ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, ray->dist));
	l = length_v3d(sub_v3d(ray->inter, pos));
	l /= cos(a[0]);
	if (dot_v3d(n, sub_v3d(ray->inter, pos)) < 0)
		l *= -1;
	ray->norm = unit_v3d(sub_v3d(ray->inter, add_v3d(pos, smul_v3d(n, l))));
}

static int	find_dist(t_ray *ray, double *sol, t_v3d *p, double *a)
{
	int		i;
	double	max;
	int		index;

	i = -1;
	max = ray->dist;
	while (++i < 4)
		if (sol[i] > 0 && sol[i] < max)
		{
			index = i;
			max = sol[i];
		}
	if (max < ray->dist)
	{
		ray->dist = max;
		if (index == 0 || index == 1)
			set_cone_norm(ray, p, a);
		else if (index == 2)
			ray->norm = unit_v3d(sub_v3d(p[4], p[3]));
		else if (index == 3)
			ray->norm = unit_v3d(sub_v3d(p[3], p[4]));
		return (1);
	}
	return (0);
}

static int	find_solutions(t_ray *ray, t_v3d abc, t_v3d *p, double *a)
{
	t_v3d	p2;
	t_v3d	tmp;
	t_v3d	n;
	double	det;
	double	sol[4];

	p2 = p[4];
	n = p[0];
	if ((det = ft_solve_quadratic(abc.x, abc.y, abc.z, sol)) >= 0)
	{
		sol[2] = -1;
		while (++sol[2] < 2)
			if (sol[(int)sol[2]] >= 0)
			{
				tmp = add_v3d(ray->pos, smul_v3d(ray->dir, sol[(int)sol[2]]));
				if (!(dot_v3d(n, sub_v3d(tmp, p[3])) > 0 &&
							dot_v3d(n, sub_v3d(tmp, p2)) < 0))
					sol[(int)sol[2]] = -1;
			}
		sol[2] = caps(ray, a[2], n, p2);
		sol[3] = caps(ray, a[1], smul_v3d(n, -1), p[3]);
		if (find_dist(ray, sol, p, a))
			return (1);
	}
	return (0);
}

static void	get_param(t_object *obj, t_v3d *p)
{
	p[3] = obj->pos;
	p[4] = v3d(obj->param[2], obj->param[3], obj->param[4]);
	p[5] = add_v3d(p[3], smul_v3d(smul_v3d(sub_v3d(p[4], p[3]), obj->param[0]),
				1 / (obj->param[0] - obj->param[1])));
	p[0] = unit_v3d(sub_v3d(p[4], p[3]));
}

void		cone(t_object *obj, t_ray *ray)
{
	t_v3d	p[6];
	t_v3d	abc;
	double	tmp;
	double	a[3];

	get_param(obj, p);
	p[1] = sub_v3d(ray->pos, p[5]);
	a[0] = atan((obj->param[0] - obj->param[1]) /
											length_v3d(sub_v3d(p[4], p[3])));
	a[1] = pow(sin(a[0]), 2.0);
	a[2] = pow(cos(a[0]), 2.0);
	p[2] = sub_v3d(ray->dir, smul_v3d(p[0], dot_v3d(ray->dir, p[0])));
	abc.x = a[2] * dot_v3d(p[2], p[2]) - a[1] * dot_v3d(p[0], ray->dir) *
		dot_v3d(p[0], ray->dir);
	tmp = 2 * a[2] * dot_v3d(sub_v3d(ray->dir, smul_v3d(p[0], dot_v3d(p[0],
			ray->dir))), sub_v3d(p[1], smul_v3d(p[0], dot_v3d(p[1], p[0]))));
	abc.y = tmp - 2 * a[1] * dot_v3d(p[0], ray->dir) * dot_v3d(p[1], p[0]);
	p[2] = sub_v3d(p[1], smul_v3d(p[0], dot_v3d(p[1], p[0])));
	abc.z = a[2] * dot_v3d(p[2], p[2]) - a[1] *
			dot_v3d(p[1], p[0]) * dot_v3d(p[1], p[0]);
	a[1] = obj->param[0];
	a[2] = obj->param[1];
	if (find_solutions(ray, abc, p, a))
		ray->obj = obj;
}
