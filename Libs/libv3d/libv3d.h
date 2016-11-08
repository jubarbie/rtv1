/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libv3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:51:03 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/08 13:49:34 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBV3D_H
# define LIBV3D_H

# include <math.h>
# include <stdio.h>
# include "libft.h"

typedef struct	s_v3d
{
	float	x;
	float	y;
	float	z;
}				t_v3d;

t_v3d			v3d(float x, float y, float z);
void			print_v3d(t_v3d v);
t_v3d			add_v3d(t_v3d v1, t_v3d v2);
t_v3d			sub_v3d(t_v3d v1, t_v3d v2);
t_v3d			smul_v3d(t_v3d v, float	nb);
float			dot_v3d(t_v3d v1, t_v3d v2);
t_v3d			cross_v3d(t_v3d v1, t_v3d v2);
t_v3d			unit_v3d(t_v3d v);
float			length_v3d(t_v3d v);
float			cos_v3d(t_v3d v1, t_v3d v2);

#endif
