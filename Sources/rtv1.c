/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 13:01:24 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/12 20:55:11 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			create_img(t_env *e)
{
	int			i;
	pthread_t	th[NB_TH];

	i = -1;
	while (++i < NB_TH)
		if (pthread_create(&th[i], NULL, &raytracer, (void *)(e->param[i])) < 0)
			error_perso(e, "create thread failed");
	i = -1;
	while (++i < NB_TH)
		(void)pthread_join(th[i], NULL);
	mlx_put_image_to_window(MLX, WIN, IMG, 40, 0);
	return (0);
}

void		img_put_pixel(t_img *img, int x, int y, unsigned int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char t;

	t = ((color & 0xFF000000) >> 24);
	b = ((color & 0x00FF0000) >> 16);
	g = ((color & 0x00FF00) >> 8);
	r = (color & 0x00FF);
	img->addr[y * img->sizeline + x * (img->bpp / 8)] = r;
	img->addr[y * img->sizeline + x * (img->bpp / 8) + 1] = g;
	img->addr[y * img->sizeline + x * (img->bpp / 8) + 2] = b;
	img->addr[y * img->sizeline + x * (img->bpp / 8) + 3] = t;
}

int			main(int ac, char **av)
{
	t_env	*e;
	char	opt;
	int		i;

	if (ac - (i = get_options(ac, av, &opt)) <= 1)
		error_usage();
	e = init_env(av[i + 1], opt);
	create_img(e);
	mlx_loop_hook(MLX, moves, e);
	mlx_hook(WIN, 17, Button1MotionMask, quit_rt, e);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key_press, e);
	mlx_hook(WIN, KeyRelease, KeyReleaseMask, ft_key_release, e);
	mlx_hook(WIN, ButtonPress, ButtonPressMask, ft_mouse_click, e);
	mlx_loop(MLX);
	return (0);
}
