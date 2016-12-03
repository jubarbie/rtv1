/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 19:55:56 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/03 17:11:40 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plane(t_object *obj, t_ray *ray)
{
	t_v3d	n;
	t_v3d	q;
	double	t;
	double	det;

	n = unit_v3d(v3d(obj->param[0], obj->param[1], obj->param[2]));
	det = dot_v3d(n, ray->dir);
	if (det < 0.0000001)
	{
		q = sub_v3d(obj->pos, ray->pos);
		t = dot_v3d(q, n) / det;
		if (t > 0.0000001 && t < ray->dist)
		{
			ray->det = det;
			ray->obj = obj;
			ray->dist = t;
			ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t));
			ray->norm = n;
		}
	}
}

/*void	plane(t_object *form, t_ray *ray)
  {
  float d;
  float div;
  float t;
  t_v3d	n;

  n = unit_v3d(v3d(form->param[0], form->param[1], form->param[2]));
  div = dot_v3d(n, ray->dir);
  if (div != 0)
  {
  	d = - dot_v3d(form->pos, n);
  	t = - ((dot_v3d(n, sub_v3d(ray->pos, form->pos)) + d) / div);
  	if (t > pow(10, -6) && t < ray->dist)
  	{
  		ray->dist = t;
  		ray->obj = form;
  		ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t));
  		ray->norm = n;
  	}
  }
}*/
