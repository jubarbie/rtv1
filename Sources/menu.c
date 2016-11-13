/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 13:16:40 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/13 20:04:02 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	create_wait_image(t_env *e)
{
	int x;
	int	y;

	WAIT_IMG = mlx_new_image(MLX, IMG_WIDTH, IMG_HEIGHT);
	WAIT_ADDR = mlx_get_data_addr(WAIT_IMG, &e->wait.bpp, &e->wait.sizeline,
			&ENDIAN);
	y = -1;
	while (++y < IMG_HEIGHT)
	{
		x = -1;
		while (++x < IMG_WIDTH)
			img_put_pixel(&e->wait, x, y, 0x00FFFFFF);
	}
}

void	init_menu(t_env *e)
{
	char	*btn[NB_BTN];
	int		i;
	int		j;

	btn[0] = ft_strdup("Images/light.xpm");
	j = -1;
	while (++j < WIN_HEIGHT)
	{
		i = -1;
		while (++i < 40)
			mlx_pixel_put(MLX, WIN, i, j, 0x00525252);
	}
	i = -1;
	while (++i < NB_BTN)
	{
		MENU[i].pos_x = 4;
		MENU[i].pos_y = 4 + i * BTN_SIZE + 4 * i;
		MENU[i].width = BTN_SIZE;
		MENU[i].height = BTN_SIZE;
		MENU[i].img.img = mlx_xpm_file_to_image(MLX, btn[i], &(MENU[i].img.width),
				&(MENU[i].img.height));
		MENU[i].img.addr = mlx_get_data_addr(MENU[i].img.img, &(MENU[i].img.bpp),
				&(MENU[i].img.sizeline), &ENDIAN);
	}
	i = -1;
	while (++i < NB_BTN)
		mlx_put_image_to_window(MLX, WIN, MENU[i].img.img,
				MENU[i].pos_x, MENU[i].pos_y);
}
