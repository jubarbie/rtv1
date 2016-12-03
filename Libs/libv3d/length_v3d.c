/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_v3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:40:33 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/03 16:59:14 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libv3d.h"

double	length_v3d(t_v3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
