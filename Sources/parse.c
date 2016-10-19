/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 16:21:36 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/19 20:02:48 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	size_to_end_acc(char *str)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '{')
			j++;
		if (str[i] == '}' && j == 0)
			return (i);
		if (str[i] == '}' && j > 0)
			j--;
		i++;
	}
	if (str[i] == '\0')
		exit(EXIT_FAILURE);
	return (10);
}

static void	get_cam_pos(t_env *e, char *str)
{
	int	i;

	while (*str == '\n' || *str == '\t' || *str == ' ')
		str++;
	i = 0;
	while (str[i] != '\n' && str[i] != '\t' && str[i] != ' ')
		i++;
	str[i] = '\0';
	e->scene->cam_pos = new_vector(2, 2, 2);
}

static void	build_scene(t_env *e, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (!(e->scene = malloc(sizeof(t_scene))))
		quit_rt(e);
	if (!(str = ft_strstr(str, "scene {")))
		quit_rt(e);
	tmp = strndup(str + 7, size_to_end_acc(str + 7));
	if (!(tmp = ft_strstr(tmp, "name {")))
		quit_rt(e);
	tmp = strndup(tmp + 6, size_to_end_acc(tmp + 6));
	e->scene->name = ft_strtrim(tmp);
	if (!(tmp = ft_strstr(tmp, "camera {")))
		e->scene->cam_pos = new_vector(0, 0, 0);
	else
		get_cam_pos(e, tmp);
}

static char	*get_file_content(t_env *e, char *file_name)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	*file;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		quit_rt(e);
	file = ft_strnew(0);
	while (get_next_line(fd, &line))
	{
		if (line[0] != '#')
		{
			tmp = file;
			file = ft_strjoin(tmp, line);
			free(tmp);
		}
		free(line);
	}
	close(fd);
	if (D)
		ft_putstr(file);
	return (file);
}

void		parse_rt(t_env *e, char *file_name)
{
	build_scene(e, get_file_content(e, file_name));
}
