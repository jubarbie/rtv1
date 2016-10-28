/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 19:55:56 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/28 14:23:22 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plane(t_param *param, t_object *obj)
{
	t_vector	n;
	double		t;

	n = fill_vector(obj->param[0], obj->param[1], obj->param[2]);
	t = (n.x * (RAY_POS.x - 0)) + (n.y * (RAY_POS.y - 0)) + (n.z * (RAY_POS.z - 0)) + obj->param[3];
	t /= n.x * RAY_DIR.x + n.y * RAY_DIR.y + n.z * RAY_DIR.z;
	t *= -1;
	//printf("t: %lf\n", t);	
	if (t == 0)
	{
		OBJ = obj;
		DIST = t;
		COLOR = obj->color;
		RAY = add_vectors(RAY_POS, time_vector(RAY_DIR, t));
	}

}
