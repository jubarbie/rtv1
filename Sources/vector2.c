/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 19:19:33 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/28 10:59:10 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	rot_vector_x(t_vector v, double angle)
{
	t_vector ret;

	ret.x = v.x;
	ret.y = v.y * cos(angle) - v.z * sin (angle);
	ret.z = v.y * sin(angle) + v.z * cos(angle);
	return (ret);
}

double		angle_vectors(t_vector v1, t_vector v2)
{
	double	ret;
	
	v1 = unit_vector(v1);
	v2 = unit_vector(v2);
	ret = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (ret);
}

t_vector	perp_vector(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = (v1.y * v2.z - v2.y * v1.z);
	ret.y = -(v1.x * v2.z - v2.x * v1.z);
	ret.z = (v1.x * v2.y - v2.x * v1.y);
	return (ret);
}

t_vector	time_vector(t_vector v, double i)
{
	t_vector	ret;

	ret.x = v.x * i;
	ret.y = v.y * i;
	ret.z = v.z * i;
	return (ret);
}

t_vector	add_vectors(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_vector	sub_vectors(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}
