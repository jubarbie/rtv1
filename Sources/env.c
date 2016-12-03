/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:06:39 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/03 18:02:51 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		init_scene(t_env *e, char *file_name)
{
	parse_rt(e, file_name);
	VW_WIDTH = 0.990000000;
	VW_HEIGHT = 0.790000000;
	VW_DIST = 1.000000000;
	GAP_X = VW_WIDTH / (double)IMG_WIDTH;
	GAP_Y = VW_HEIGHT / (double)IMG_HEIGHT;
	CAM_UP = v3d(0, 1, 0);
	CAM_DIR = v3d(0, 0, 1);
	CAM_RIGHT = v3d(1, 0, 0);
	//CAM_UP = unit_v3d(cross_v3d(CAM_RIGHT, CAM_DIR));
}

static t_param	*init_param(t_env *e, int index)
{
	t_param	*param;

	if (!(param = malloc(sizeof(t_param))))
		error_perso(e, "malloc (t_param *)param failed");
	ENV = e;
	TH = index;
	return (param);
}

static void		free_obj(void *content, size_t size)
{
	t_object	*obj;

	obj = (t_object *)content;
	free(obj->name);
	free(obj->param);
	free(obj);
	content = NULL;
	size = 0;
}

void			free_env(t_env *e)
{
	int	i;

	if (e)
	{
		i = -1;
		while (++i < NB_TH)
			e->param[i] ? free(e->param[i]) : 0;
		e->scene->name ? free(e->scene->name) : 0;
		ft_lstdel(&e->scene->obj, &free_obj);
		ft_lstdel(&e->scene->light, &free_obj);
		e->scene ? free(e->scene) : 0;
		mlx_destroy_image(MLX, IMG);
		MLX = NULL;
		WIN = NULL;
		IMG = NULL;
		free(e);
	}
}

t_env			*init_env(char *file_name, char opt)
{
	t_env	*e;
	int		i;

	if (!(e = (t_env *)malloc(sizeof(t_env))))
		error_perso(e, "malloc (t_env *)e failed");
	OPT = opt;
	init_scene(e, file_name);
	i = -1;
	while (++i < NB_TH)
		e->param[i] = init_param(e, i);
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, WIN_WIDTH, WIN_HEIGHT, "RT v.1");
	init_menu(e);
	IMG = mlx_new_image(MLX, IMG_WIDTH, IMG_HEIGHT);
	IMG_ADDR = mlx_get_data_addr(IMG, &e->img.bpp, &e->img.sizeline, &ENDIAN);
	create_wait_image(e);
	debug(e);
	return (e);
}
