/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 13:01:24 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/20 11:39:20 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	create_img(t_env *e)
{
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	return (0);
}

void	img_put_pixel(t_env *e, int x, int y, unsigned int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	b = ((color & 0x00FF0000) >> 16);
	g = ((color & 0x00FF00) >> 8);
	r = (color & 0x00FF);
	IMG_ADDR[y * SIZELINE + x * (BPP / 8)] = r;
	IMG_ADDR[y * SIZELINE + x * (BPP / 8) + 1] = g;
	IMG_ADDR[y * SIZELINE + x * (BPP / 8) + 2] = b;
}

int		main(int ac, char **av)
{
	int		i;
	t_env	*e;

	e = init_env(900, 700);
	i = get_options(ac, av, &OPT);
	parse_rt(e, av[i + 1]);
	if (D)
	{
		printf("Number of options: %d\n", i);
		debug(e);
	}
	mlx_loop_hook(MLX, create_img, e);
	mlx_hook(WIN, 17, Button1MotionMask, quit_rt, e);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key_press, e);
	mlx_hook(WIN, KeyRelease, KeyReleaseMask, ft_key_release, e);
	mlx_loop(MLX);
	return (0);
}
