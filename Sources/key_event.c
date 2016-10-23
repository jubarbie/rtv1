/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:06:00 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/23 19:52:53 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_key_release(int keycode, t_env *e)
{
	if (D)
		printf("%d\n", keycode);
	return (0);
}

int			ft_key_press(int keycode, t_env *e)
{
	if (D)
		printf("%d\n", keycode);
	if (keycode == 53)
		quit_rt(e);
	else if (keycode == 126)
		CAM_POS.x -= 0.1;
	else if (keycode == 125)
		CAM_POS.x += 0.1;
	else if (keycode == 124)
		CAM_POS.y -= 0.1;
	else if (keycode == 123)
		CAM_POS.y += 0.1;
	else if (keycode == 43)
		CAM_POS.z -= 0.1;
	else if (keycode == 47)
		CAM_POS.z += 0.1;
	else if (keycode == 78)
		VW_DIST -= 1;
	else if (keycode == 69)
		VW_DIST += 1;
	return (0);
}
