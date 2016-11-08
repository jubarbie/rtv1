/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smul_v3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:16:04 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/08 12:17:35 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libv3d.h"

t_v3d	smul_v3d(t_v3d v, float	nb)
{
	t_v3d	ret;

	ret.x = v.x * nb;
	ret.y = v.y * nb;
	ret.z = v.z * nb;
	return (ret);
}
