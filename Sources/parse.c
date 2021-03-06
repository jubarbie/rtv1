/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 16:21:36 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/12 20:53:37 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*go_to_next_acc(t_env *e, char *str, int n)
{
	char	*tmp;

	tmp = str;
	while ((*tmp == '\n' || *tmp == '\t' || *tmp == ' ') && tmp != '\0'
																	&& n-- > 0)
		tmp++;
	if (*tmp != '{')
		error_perso(e, "Missing one \"{\" in file");
	return (++tmp);
}

void		check_acc(t_env *e, char *str)
{
	int		i;
	int		nb;

	i = -1;
	nb = 0;
	while (str[++i] && nb >= 0)
	{
		if (str[i] == '{')
			nb++;
		else if (str[i] == '}')
			nb--;
	}
	if (nb != 0)
		error_perso(e, "missing one \"}\" in file");
}

int			size_to_end_acc(t_env *e, char *str)
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
		error_perso(e, "missing one \"}\" in file");
	return (-1);
}

t_v3d		get_v3d(t_env *e, char *str, int n, char *name)
{
	char	*tmp;
	char	*tmpy;
	char	*tmpz;

	if (!(tmp = ft_strnstr(str, name, n)))
		return (v3d(0, 0, 0));
	else
	{
		tmp = go_to_next_acc(e, tmp + ft_strlen(name), n);
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
		return (v3d(ft_atof(tmp), ft_atof(tmpy), ft_atof(tmpz)));
	}
}

char		*get_in_acc(t_env *e, char *str, char *acc, int n)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	int		len;

	if (!(tmp = ft_strnstr(str, acc, n)))
		error_perso(e, "malloc failed in get_in_acc function");
	len = ft_strlen(acc);
	tmp = go_to_next_acc(e, tmp + len, n);
	tmp1 = strndup(tmp, size_to_end_acc(e, tmp));
	tmp2 = ft_strtrim(tmp1);
	free(tmp1);
	return (tmp2);
}
