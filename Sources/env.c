/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:06:39 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/21 20:24:06 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		init_scene(t_env *e, char *file_name)
{
	parse_rt(e, file_name);
	CAM_DIR = unit_vector(fill_vector(-CAM_POS.x, -CAM_POS.y, -CAM_POS.z));
	VW_WIDTH = 0.35;
	VW_HEIGHT = 0.5;
	VW_DIST = 1.0;
	CAM_UP = unit_vector(fill_vector(0, 1, 0));
	CAM_RIGHT = unit_vector(perp_vector(CAM_UP, CAM_DIR));
	VW_UP_LEFT = add_vectors(CAM_POS, sub_vectors(add_vectors(
				time_vector(CAM_DIR, VW_DIST), time_vector(
				CAM_UP, VW_HEIGHT / 2)), time_vector(CAM_RIGHT, VW_WIDTH / 2)));
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

static void		free_obj(void *content, size_t size)
{
	t_object	*obj;

	obj = (t_object *)content;
	free(obj->name);
	free(obj->type);
	free(obj->param);
	free(obj);
	content = NULL;
	size = 0;
}

void			free_env(t_env *e)
{
	int	i;

	i = -1;
	while (++i < NB_TH)
		free(e->param[i]);
	free(e->scene->name);
	ft_lstdel(&e->scene->obj, &free_obj);
	free(e->scene);
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
