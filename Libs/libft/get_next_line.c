/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:19:47 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/20 20:55:04 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static void		free_all(char **line, t_list **first, int fd)
{
	t_list	*todel;
	t_list	*prev;

	prev = *first;
	todel = *first;
	if ((*first)->content_size == (size_t)fd)
		*first = (*first)->next;
	else
	{
		while (prev->next)
		{
			if (prev->next->content_size == (size_t)fd)
			{
				todel = prev->next;
				prev->next = prev->next->next;
				break ;
			}
			prev = prev->next;
		}
	}
	free(todel->content);
	free(todel);
	free(*line);
}

static t_list	*search_fd(t_list **first, int fd)
{
	t_list	*elem;
	char	*buf;

	elem = *first;
	while (elem)
	{
		if (elem->content_size == (size_t)fd)
			return (elem);
		elem = elem->next;
	}
	elem = *first;
	buf = ft_strnew(BUFF_SIZE);
	ft_lstadd(first, ft_lstnew(buf, BUFF_SIZE + 1));
	free(buf);
	(*first)->content_size = fd;
	return (*first);
}

static int		treat_buff(int fd, char *buff, char **line)
{
	int		i;
	int		nl;
	int		ret;
	char	*temp;

	i = 0;
	nl = 0;
	while (i < BUFF_SIZE && buff[i])
		if (buff[i++] == '\n')
		{
			buff[i - 1] = '\0';
			nl = 1;
			break ;
		}
	temp = ft_strjoin(*line, buff);
	free(*line);
	*line = temp;
	ft_memmove(buff, &buff[i], BUFF_SIZE - i);
	ret = read(fd, &buff[BUFF_SIZE - i], i);
	buff[BUFF_SIZE - i + ret] = '\0';
	if (nl == 1 || !ret)
		return (1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*first = NULL;
	char			*buff;
	int				ret;

	if (fd < 0 || !line || !(*line = ft_strnew(0)))
		return (-1);
	buff = (search_fd(&first, fd))->content;
	ret = 1;
	if (!*(buff))
		if ((ret = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
	while (*buff)
	{
		if (treat_buff(fd, buff, line))
			return (1);
	}
	free_all(line, &first, fd);
	return (0);
}
