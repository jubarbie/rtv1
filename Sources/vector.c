/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:07:04 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/30 16:30:54 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		print_vector(t_vector v, char *str)
{
	printf("%s (%lf, %lf, %lf)\n", str, v.x, v.y, v.z);
}

double		norm_vector(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
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
