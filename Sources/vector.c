/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:07:04 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/19 17:11:13 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		rot_vector(t_vector *v, double a)
{
	double tmp;

	tmp = v->x;
	v->x = (v->x * cos(a)) + (v->y * sin(a));
	v->y = (tmp * -sin(a)) + (v->y * cos(a));
}

void		time_vector(t_vector *v, double i)
{
	v->x *= i;
	v->y *= i;
}

void		add_vectors(t_vector *v1, t_vector *v2)
{
	v1->x += v2->x;
	v1->y += v2->y;
}

void		sub_vectors(t_vector *v1, t_vector *v2)
{
	v1->x -= v2->x;
	v1->y -= v2->y;
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
