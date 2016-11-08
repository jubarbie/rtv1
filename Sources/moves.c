/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 17:50:44 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/08 16:14:51 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		moves(t_env *e)
{
	if (MOVES & M_UP)
		CAM_POS = add_v3d(CAM_POS, smul_v3d(CAM_UP, SPEED));
		//CAM_DIR = unit_v3d(add_v3d(CAM_DIR, smul_v3d(CAM_UP, 0.01)));
	if (MOVES & M_DOWN)
		CAM_POS = sub_v3d(CAM_POS, smul_v3d(CAM_UP, SPEED));
		//CAM_DIR = unit_v3d(sub_v3d(CAM_DIR, smul_v3d(CAM_UP, 0.01)));
	if (MOVES & M_LEFT)
		CAM_POS = add_v3d(CAM_POS, smul_v3d(CAM_RIGHT, SPEED));
		//CAM_DIR = unit_v3d(sub_v3d(CAM_DIR, smul_v3d(CAM_RIGHT, 0.01)));
	if (MOVES & M_RIGHT)
		CAM_POS = sub_v3d(CAM_POS, smul_v3d(CAM_RIGHT, SPEED));
		//CAM_DIR = unit_v3d(add_v3d(CAM_DIR, smul_v3d(CAM_RIGHT, 0.01)));
	if (MOVES & M_FORWARD)
		CAM_POS = add_v3d(CAM_POS, smul_v3d(CAM_DIR, SPEED));
	if (MOVES & M_BACKWARD)
		CAM_POS = sub_v3d(CAM_POS, smul_v3d(CAM_DIR, SPEED));
	if (MOVES > 0)
		create_img(e);
	return (0);
}
