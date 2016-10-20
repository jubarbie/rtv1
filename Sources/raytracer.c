/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 15:41:19 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/20 17:03:49 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	*raytracer(void *arg)
{
	int		x;
	int		y;
	t_env	*e;
	t_param	*param;

	param = (t_param *)arg;
	e = ENV;
	x = TH * (WIN_WIDTH / NB_TH) - 1;
	while (++x < (TH + 1) * WIN_WIDTH / NB_TH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
			img_put_pixel(e, x, y, 0x00FF0000);
	}
	pthread_exit(0);
}
