/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:06:39 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/12 20:55:08 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		init_scene(t_env *e, char *file_name)
{
	parse_rt(e, file_name);
	VW_WIDTH = IMG_WIDTH / 1000.0;
	VW_HEIGHT = IMG_HEIGHT / 1000.0;
	VW_DIST = 1.0;
	GAP_X = VW_WIDTH / (double)IMG_WIDTH;
	GAP_Y = VW_HEIGHT / (double)IMG_HEIGHT;
	CAM_DIR = unit_v3d(CAM_DIR);
	CAM_UP = v3d(0, 1.0, 0);
	if (CAM_DIR.y == fmax(fmax(CAM_DIR.x, CAM_DIR.y), CAM_DIR.z))
		CAM_UP = v3d(0, 0, 1);
	if (CAM_DIR.y == fmin(fmin(CAM_DIR.x, CAM_DIR.y), CAM_DIR.z) &&
																CAM_DIR.y < 0)
		CAM_UP = v3d(0, 0, -1);
	CAM_RIGHT = cross_v3d(CAM_UP, CAM_DIR);
	VW_DIST = 1.0;
	CAM_UP = cross_v3d(CAM_DIR, CAM_RIGHT);
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
	if (ft_strcmp(file_name + ft_strlen(file_name) - 3, ".rt"))
		error_perso(e, "Bad file extension (.rt)");
	OPT = opt;
	OPT |= (1 << 1);
	init_scene(e, file_name);
	i = -1;
	while (++i < NB_TH)
		e->param[i] = init_param(e, i);
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, WIN_WIDTH, WIN_HEIGHT, "RT v.1");
	init_menu(e);
	IMG = mlx_new_image(MLX, (S) ? IMG_WIDTH / 2 : IMG_WIDTH, IMG_HEIGHT);
	IMG_ADDR = mlx_get_data_addr(IMG, &e->img.bpp, &e->img.sizeline, &ENDIAN);
	debug(e);
	return (e);
}
