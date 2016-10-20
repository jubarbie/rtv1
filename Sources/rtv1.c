/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 13:01:24 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/20 17:54:29 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	create_img(t_env *e)
{
	int			i;
	pthread_t	th[NB_TH];

	i = -1;
	while (++i < NB_TH)
		if (pthread_create(&th[i], NULL, &raytracer, (void *)(e->param[i])) < 0)
				quit_rt(e);
	i = -1;
	while (++i < NB_TH)
		(void)pthread_join(th[i], NULL);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	return (0);
}

void		img_put_pixel(t_env *e, int x, int y, unsigned int color)
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

int			main(int ac, char **av)
{
	t_env	*e;
	char	opt;

	e = init_env(av[get_options(ac, av, &opt) + 1], opt);
	mlx_loop_hook(MLX, create_img, e);
	mlx_hook(WIN, 17, Button1MotionMask, quit_rt, e);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key_press, e);
	mlx_hook(WIN, KeyRelease, KeyReleaseMask, ft_key_release, e);
	mlx_loop(MLX);
	return (0);
}
