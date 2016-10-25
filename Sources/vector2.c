/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 19:19:33 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/25 19:23:45 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	t_vector	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}
