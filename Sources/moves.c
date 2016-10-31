/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 17:50:44 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/31 16:13:24 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		moves(t_env *e)
{
	if (MOVES & M_UP)
		CAM_POS = add_vectors(CAM_POS, time_vector(CAM_UP, 0.1));
		//CAM_DIR = unit_vector(add_vectors(CAM_DIR, time_vector(CAM_UP, 0.01)));
	if (MOVES & M_DOWN)
		CAM_POS = sub_vectors(CAM_POS, time_vector(CAM_UP, 0.1));
		//CAM_DIR = unit_vector(sub_vectors(CAM_DIR, time_vector(CAM_UP, 0.01)));
	if (MOVES & M_LEFT)
		CAM_POS = add_vectors(CAM_POS, time_vector(CAM_RIGHT, 0.1));
		//CAM_DIR = unit_vector(sub_vectors(CAM_DIR, time_vector(CAM_RIGHT, 0.01)));
	if (MOVES & M_RIGHT)
		CAM_POS = sub_vectors(CAM_POS, time_vector(CAM_RIGHT, 0.1));
		//CAM_DIR = unit_vector(add_vectors(CAM_DIR, time_vector(CAM_RIGHT, 0.01)));
	if (MOVES & M_FORWARD)
		CAM_POS = add_vectors(CAM_POS, time_vector(CAM_DIR, 0.1));
	if (MOVES & M_BACKWARD)
		CAM_POS = sub_vectors(CAM_POS, time_vector(CAM_DIR, 0.1));
	if (MOVES > 0)
		create_img(e);
	return (0);
}
