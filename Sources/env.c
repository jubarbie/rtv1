/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:06:39 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/20 19:03:19 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		init_scene(t_env *e, char *file_name)
{
	parse_rt(e, file_name);
	CAM_DIR = fill_vector(0 - CAM_POS->x, 0 - CAM_POS->y, 0 - CAM_POS->z);
	VW_WIDTH = 0.35;
	VW_HEIGHT = 0.5;
	VW_DIST = 1.0;
	CAM_UP = fill_vector(0, 1, 0);
	CAM_LEFT = perp_vector(CAM_UP);
	VW_UP_LEFT;
}

static t_param	*init_param(t_env *e, int index)
{
	t_param	*param;

	if (!(param = malloc(sizeof(t_param))))
		exit(EXIT_FAILURE);
	ENV = e;
	TH = index;
	return (param);
}

void			free_env(t_env *e)
{
	mlx_destroy_image(MLX, IMG);
	MLX = NULL;
	WIN = NULL;
	IMG = NULL;
	free(e);
}

t_env			*init_env(char *file_name, char opt)
{
	t_env	*e;
	int		i;

	if (!(e = (t_env *)malloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	OPT = opt;
	init_scene(e, file_name);
	i = -1;
	while (++i < NB_TH)
		e->param[i] = init_param(e, i);
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, WIN_WIDTH, WIN_HEIGHT, "RT v.1");
	IMG = mlx_new_image(MLX, WIN_WIDTH, WIN_HEIGHT);
	IMG_ADDR = mlx_get_data_addr(IMG, &BPP, &SIZELINE, &ENDIAN);
	debug(e);
	return (e);
}
