/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_v3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:25:53 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/08 12:27:15 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libv3d.h"

t_v3d	cross_v3d(t_v3d v1, t_v3d v2)
{
	t_v3d ret;
	
	ret.x = (v1.y * v2.z - v2.y * v1.z);
	ret.y = -(v1.x * v2.z - v2.x * v1.z);
	ret.z = (v1.x * v2.y - v2.x * v1.y);
	return (ret);
}
