/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:06:00 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/19 17:10:40 by jubarbie         ###   ########.fr       */
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
	return (0);
}
