/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 13:16:40 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/09 19:06:09 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	back_menu(t_env *e)
{
	int	i;
	int	j;

	j = -1;
	while (++j < WIN_HEIGHT)
	{
		i = -1;
		while (++i < 40)
			mlx_pixel_put(MLX, WIN, i, j, 0x00525252);
	}
}

void		init_menu(t_env *e)
{
	char	*btn[NB_BTN];
	int		i;

	btn[0] = ft_strdup("Images/light.xpm");
	back_menu(e);
	i = -1;
	while (++i < NB_BTN)
	{
		MENU[i].pos_x = 4;
		MENU[i].pos_y = 4 + i * BTN_SIZE + 4 * i;
		MENU[i].width = BTN_SIZE;
		MENU[i].height = BTN_SIZE;
		MENU[i].img.img = mlx_xpm_file_to_image(MLX, btn[i],
				&(MENU[i].img.width), &(MENU[i].img.height));
		MENU[i].img.addr = mlx_get_data_addr(MENU[i].img.img,
				&(MENU[i].img.bpp), &(MENU[i].img.sizeline), &ENDIAN);
	}
	i = -1;
	while (++i < NB_BTN)
		mlx_put_image_to_window(MLX, WIN, MENU[i].img.img,
												MENU[i].pos_x, MENU[i].pos_y);
	free(btn[0]);
}
