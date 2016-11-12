/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 17:50:44 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/12 15:35:34 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		moves(t_env *e)
{
	if (MOVES & M_UP)
		CAM_POS = add_v3d(CAM_POS, smul_v3d(CAM_UP, SPEED));
	if (MOVES & M_DOWN)
		CAM_POS = sub_v3d(CAM_POS, smul_v3d(CAM_UP, SPEED));
	if (MOVES & M_LEFT)
		CAM_POS = add_v3d(CAM_POS, smul_v3d(CAM_RIGHT, SPEED));
	if (MOVES & M_RIGHT)
		CAM_POS = sub_v3d(CAM_POS, smul_v3d(CAM_RIGHT, SPEED));
	if (MOVES & M_FORWARD)
		CAM_POS = add_v3d(CAM_POS, smul_v3d(CAM_DIR, SPEED));
	if (MOVES & M_BACKWARD)
		CAM_POS = sub_v3d(CAM_POS, smul_v3d(CAM_DIR, SPEED));
	if (MOVES > 0)
		create_img(e);
	return (0);
}
