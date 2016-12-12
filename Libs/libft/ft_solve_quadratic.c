/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_quadratic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 08:30:02 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/12 18:59:07 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_solve_quadratic(double a, double b, double c, double *t)
{
	double det;

	det = (b * b) - (4.0 * a * c);
	if (det >= 0)
	{
		t[0] = (-b + sqrt(det)) / (2.0 * a);
		t[1] = (-b - sqrt(det)) / (2.0 * a);
		return (det);
	}
	return (det);
}
