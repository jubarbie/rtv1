/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:07:04 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/21 15:29:47 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		rot_vector(t_vector v, double a)
{
	double tmp;

	tmp = v.x;
	v.x = (v.x * cos(a)) + (v.y * sin(a));
	v.y = (tmp * -sin(a)) + (v.y * cos(a));
}

t_vector	perp_vector(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = (v1.y * v2.z - v2.y * v1.z);
	ret.y = (v1.x * v2.z - v2.x * v1.z);
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
	t_vector 	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

double		norm_vector(t_vector v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	unit_vector(t_vector v)
{
	t_vector	ret;
	double		norm;

	norm = norm_vector(v);
	ret.x = v.x / norm;
	ret.y = v.y / norm;
	ret.z = v.z / norm;
	return (ret);
}

t_vector	fill_vector(double x, double y, double z)
{
	t_vector	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vector	*new_vector(double x, double y, double z)
{
	t_vector *v;

	if ((v = malloc(sizeof(t_vector))) == NULL)
		exit(EXIT_FAILURE);
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}
