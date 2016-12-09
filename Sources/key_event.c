/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:06:00 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/09 16:26:37 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	move(int keycode, t_env *e)
{
	if (keycode == 126)
		MOVES |= M_UP;
	else if (keycode == 125)
		MOVES |= M_DOWN;
	else if (keycode == 123)
		MOVES |= M_LEFT;
	else if (keycode == 124)
		MOVES |= M_RIGHT;
	else if (keycode == 13)
		MOVES |= M_FORWARD;
	else if (keycode == 1)
		MOVES |= M_BACKWARD;
}

int			ft_key_release(int keycode, t_env *e)
{
	if (keycode == 126)
		MOVES ^= M_UP;
	else if (keycode == 125)
		MOVES ^= M_DOWN;
	else if (keycode == 123)
		MOVES ^= M_LEFT;
	else if (keycode == 124)
		MOVES ^= M_RIGHT;
	else if (keycode == 13)
		MOVES ^= M_FORWARD;
	else if (keycode == 1)
		MOVES ^= M_BACKWARD;
	return (0);
}

int			ft_key_press(int keycode, t_env *e)
{
	if (D)
		printf("%d\n", keycode);
	if (keycode == 53)
		quit_rt(e);
	else if (keycode == 37)
	{
		(L) ? (OPT ^= (1 << 1)) : (OPT |= (1 << 1));
		create_img(e);
	}
	else
		move(keycode, e);
	return (0);
}
