/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 19:55:56 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/30 11:50:27 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plane(t_object *obj, t_ray *ray)
{
	t_vector	n;
	double		t;

	n = fill_vector(obj->param[0], obj->param[1], obj->param[2]);
	t = (n.x * (ray->pos.x - 0)) + (n.y * (ray->pos.y - 0)) + (n.z * (ray->pos.z - 0)) + obj->param[3];
	t /= n.x * ray->dir.x + n.y * ray->dir.y + n.z * ray->dir.z;
	t *= -1;
	if (t < 0)
	{
		ray->obj = obj;
		ray->dist = t;
		ray->inter = add_vectors(ray->pos, time_vector(ray->dir, t));
	}

}
