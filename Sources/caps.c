/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:38:22 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/10 16:51:41 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	caps_up(t_object *obj, t_ray *ray)
{
	t_v3d	n;
	t_v3d	p2;
	t_v3d	tmp;
	double	r;
	double	det;

	r = obj->param[0];
	p2 = v3d(obj->param[1], obj->param[2], obj->param[3]);
	n = unit_v3d(sub_v3d(p2, obj->pos));
	det = dot_v3d(n, ray->dir);
	if (det < 0.0000001 || det > 0.0000001)
	{
		tmp = sub_v3d(p2, ray->pos);
		det = dot_v3d(tmp, n) / det;
		if (det > 0)
		{
			tmp = add_v3d(ray->pos, smul_v3d(ray->dir, det));
			if (dot_v3d(sub_v3d(tmp, p2), sub_v3d(tmp, p2)) >= r * r)
				return (-1);
			return (det);
		}
	}
	return (-1);
}

double	caps_bottom(t_object *obj, t_ray *ray)
{
	t_v3d	n;
	t_v3d	p1;
	t_v3d	tmp;
	double	r;
	double	det;

	r = obj->param[0];
	p1 = obj->pos;
	n = unit_v3d(sub_v3d(p1, v3d(obj->param[1], obj->param[2], obj->param[3])));
	det = dot_v3d(n, ray->dir);
	if (det < 0.0000001 || det > 0.0000001)
	{
		tmp = sub_v3d(p1, ray->pos);
		det = dot_v3d(tmp, n) / det;
		if (det > 0)
		{
			tmp = add_v3d(ray->pos, smul_v3d(ray->dir, det));
			if (dot_v3d(sub_v3d(tmp, p1), sub_v3d(tmp, p1)) >= r * r)
				return (-1);
			return (det);
		}
	}
	return (-1);
}

double	caps(t_ray *ray, double r, t_v3d n, t_v3d p)
{
	t_v3d	tmp;
	double	det;

	det = dot_v3d(n, ray->dir);
	if (det < 0.0000001 || det > 0.0000001)
	{
		tmp = sub_v3d(p, ray->pos);
		det = dot_v3d(tmp, n) / det;
		if (det > 0)
		{
			tmp = add_v3d(ray->pos, smul_v3d(ray->dir, det));
			if (dot_v3d(sub_v3d(tmp, p), sub_v3d(tmp, p)) >= r * r)
				return (-1);
			return (det);
		}
	}
	return (-1);
}
