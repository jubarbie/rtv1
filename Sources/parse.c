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

static void	get_origin(t_env *e, char *str, int n)
{
	char	*tmp;
	char	*tmpy;
	char	*tmpz;
	
	if (!(tmp = ft_strnstr(str, "origin {", n)))
		e->scene->cam_pos = new_vector(0, 0, 0);
	else
	{
		tmp += 8;
		while ((*tmp == '\n' || *tmp == '\t' || *tmp == ' ') && n-- > 0)
			tmp++;
		tmpy = tmp;
		while (*tmpy != '\n' && *tmpy != '\t' && *tmpy != ' ' && n-- > 0)
			tmpy++;
		while ((*tmpy == '\n' || *tmpy == '\t' || *tmpy == ' ') && n-- > 0)
			tmpy++;
		tmpz = tmpy;
		while (*tmpz != '\n' && *tmpz != '\t' && *tmpz != ' ' && n-- > 0)
			tmpz++;	
		e->scene->cam_pos = new_vector(atof(tmp), atof(tmpy), atof(tmpz));
	}
}

static void	get_name(t_env *e, char *str, int n)
{
	char *tmp;
	
	tmp = strndup(str, n);
	e->scene->name = ft_strtrim(tmp);
	free(tmp);
}

static void buid_object(t_env *e, char *str, int n)
{
	if (!(e->scene->obj))
			
}

static void	build_scene(t_env *e, char *str)
{
	char	*tmp;

	if (!(e->scene = malloc(sizeof(t_scene))))
		quit_rt(e);
	e->scene->obj = NULL;
	if (!(str = ft_strstr(str, "scene {")))
		quit_rt(e);
	str += 7;
	if (!(tmp = ft_strnstr(str, "name {", size_to_end_acc(str))))
		quit_rt(e);
	get_name(e, tmp + 6, size_to_end_acc(tmp + 6));
	if (!(tmp = ft_strnstr(str , "camera {", size_to_end_acc(str))))
		e->scene->cam_pos = new_vector(0, 0, 0);
	else
		get_origin(e, tmp + 8, size_to_end_acc(tmp + 8));
	while (tmp = ft_strnstr(str, "object {", size_to_end_acc(str)))
	{
		tmp += 8;
		get_object(e, tmp, size_to_end_acc(tmp));
	}
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
	char	*str;

	str = get_file_content(e, file_name);
	build_scene(e, str);
	free(str);
}
