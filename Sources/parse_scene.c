/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 16:21:36 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/12 20:55:09 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	free_fct_tab(t_env *e)
{
	int	i;

	i = -1;
	while (e->obj_allowed[++i])
		free(e->obj_allowed[i]);
	free(e->obj_allowed);
}

static void	make_fct_tab(t_env *e)
{
	e->obj_allowed = ft_strsplit(OBJ_ALLOWED, ' ');
	e->obj_fct_obj[0] = &sphere;
	e->obj_fct_obj[1] = &sphere;
	e->obj_fct_obj[2] = &plane;
	e->obj_fct_obj[3] = &sphere;
	e->obj_fct_obj[4] = &cone;
	e->obj_fct_obj[5] = &cylinder;
}

static void	build_scene(t_env *e, char *str)
{
	char	*tmp;

	if (!(e->scene = malloc(sizeof(t_scene))))
		error_perso(e, "malloc (t_scene *)scene failed");
	e->scene->obj = NULL;
	e->scene->light = NULL;
	check_acc(e, str);
	if (!(str = ft_strstr(str, "scene")))
		error_perso(e, "no scene found in file");
	str = go_to_next_acc(e, str + 5, ft_strlen(str));
	e->scene->name = get_in_acc(e, str, "name", size_to_end_acc(e, str));
	if (!(tmp = ft_strnstr(str, "camera", size_to_end_acc(e, str))))
		error_perso(e, "No camera specified in scene");
	else
	{
		tmp = go_to_next_acc(e, tmp + 6, size_to_end_acc(e, str));
		e->scene->cam_pos = get_v3d(e, tmp, size_to_end_acc(e, tmp), "origin");
		e->scene->cam_dir = get_v3d(e, tmp, size_to_end_acc(e, tmp), "dir");
	}
	tmp = str;
	while ((tmp = ft_strnstr(tmp, "object", size_to_end_acc(e, str))))
	{
		tmp = go_to_next_acc(e, tmp + 6, size_to_end_acc(e, str));
		build_object(e, tmp, size_to_end_acc(e, tmp));
	}
}

static int	avoid_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	return (i);
}

void		parse_rt(t_env *e, char *file_name)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	*file;
	int		i;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		error_perso(e, "Failed opening file");
	file = ft_strnew(0);
	while (get_next_line(fd, &line))
	{
		i = avoid_spaces(line);
		if (line[i] && line[i] != '#')
		{
			tmp = file;
			file = ft_strjoin(tmp, &line[i]);
			free(tmp);
		}
		free(line);
	}
	close(fd);
	make_fct_tab(e);
	build_scene(e, file);
	free_fct_tab(e);
	free(file);
}
