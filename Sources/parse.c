/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 16:21:36 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/20 15:41:46 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	build_scene(t_env *e, char *str)
{
	char	*tmp;

	if (!(e->scene = malloc(sizeof(t_scene))))
		quit_rt(e);
	e->scene->obj = NULL;
	if (!(str = ft_strstr(str, "scene {")))
		quit_rt(e);
	str += 7;
	e->scene->name = get_in_acc(e, str, "name {", size_to_end_acc(str));
	if (!(tmp = ft_strnstr(str, "camera {", size_to_end_acc(str))))
		e->scene->cam_pos = new_vector(0, 0, 0);
	else
		e->scene->cam_pos = get_origin(tmp + 8, size_to_end_acc(tmp + 8));
	tmp = str;
	while ((tmp = ft_strnstr(tmp, "object {", size_to_end_acc(str))))
	{
		tmp += 8;
		build_object(e, tmp, size_to_end_acc(tmp));
	}
}

int			size_to_end_acc(char *str)
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

t_vector	*get_origin(char *str, int n)
{
	char	*tmp;
	char	*tmpy;
	char	*tmpz;

	if (!(tmp = ft_strnstr(str, "origin {", n)))
		return (new_vector(0, 0, 0));
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
		return (new_vector(atof(tmp), atof(tmpy), atof(tmpz)));
	}
}

char		*get_in_acc(t_env *e, char *str, char *acc, int n)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	int		len;

	if (!(tmp = ft_strnstr(str, acc, n)))
		error_file(e);
	len = ft_strlen(acc);
	tmp1 = strndup(tmp + len, size_to_end_acc(tmp + len));
	tmp2 = ft_strtrim(tmp1);
	free(tmp1);
	return (tmp2);
}

void		parse_rt(t_env *e, char *file_name)
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
	build_scene(e, file);
	free(file);
}
