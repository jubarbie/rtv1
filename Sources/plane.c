/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 19:55:56 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/10 12:09:19 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plane(t_object *obj, t_ray *ray)
{
	t_v3d	n;
	t_v3d	q;
	float	t;
	float	det;

	n = unit_v3d(v3d(obj->param[0], obj->param[1], obj->param[2]));
	det = dot_v3d(n, ray->dir);
	if (det >= 0)
	{
		q = sub_v3d(n, ray->pos);
		t = dot_v3d(q, n) / det;
		if (t >= 0 && t < ray->dist)
		{
			ray->det = det;
			ray->obj = obj;
			ray->dist = t;
			ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t));
			ray->norm = smul_v3d(n, -1);
		}
	}
}
