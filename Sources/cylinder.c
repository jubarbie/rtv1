/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:58:17 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/03 19:53:04 by jubarbie         ###   ########.fr       */
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
	double	a;
	double	b;
	double	c;
	double	det;
	double	t0;
	double	t1;
	double	tp0;
	double	tp1;

	r = obj->param[0];
	p1 = v3d(obj->pos.x, obj->pos.y, obj->pos.z);
	p2 = v3d(obj->param[1], obj->param[2], obj->param[3]);
	n = unit_v3d(sub_v3d(p2, p1));

	dp = sub_v3d(ray->pos, obj->pos);
	tmp = sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)));
	a = dot_v3d(tmp, tmp);
	b = 2.0 * (dot_v3d((sub_v3d(ray->dir, smul_v3d(n, dot_v3d(ray->dir, n)))), 
				sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n)))));
	tmp = sub_v3d(dp, smul_v3d(n, dot_v3d(dp, n)));
	c = dot_v3d(tmp, tmp) - pow(r, 2.0);

	det = b * b  - 4.0 * a * c;
	if (det > 0.0000001)
	{
		t0 = (-b + sqrt(det)) / 2.0 * a;
		t1 = (-b - sqrt(det)) / 2.0 * a;
		tp0 = -1;
		tp1 = -1;
		if (t0 > 0.0000001)
		{
			tmp = add_v3d(ray->pos, smul_v3d(ray->dir, t0));
			if (dot_v3d(n, sub_v3d(tmp, p1)) > 0 && dot_v3d(n, sub_v3d(tmp, p2)) < 0)
				tp0 = t0;
		}
		if (t1 > 0.0000001)
		{
			tmp = add_v3d(ray->pos, smul_v3d(ray->dir, t1));
			if (dot_v3d(n, sub_v3d(tmp, p1)) > 0 && dot_v3d(n, sub_v3d(tmp, p2)) < 0)
					tp1 = t1;
		}
		if ((tp1 < tp0 && tp1 > 0) || (tp1 > tp0 && tp0 < 0))
			tp0 = tp1;
		if (tp0 > 0 && tp0 < ray->dist)
		{	
			ray->det = det;
			ray->obj = obj;
			ray->dist = tp0;
			ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, tp0));
			ray->norm = sub_v3d(ray->inter, v3d(obj->pos.x, ray->inter.y, obj->pos.z));
		}
	}
}
