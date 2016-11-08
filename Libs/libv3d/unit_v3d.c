/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_v3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:27:21 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/08 16:14:49 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libv3d.h"

t_v3d	unit_v3d(t_v3d v)
{
	float	length;

	if ((length = length_v3d(v)) != 0.0)
		return (smul_v3d(v, 1 / length));
	else
		return (v);
}
