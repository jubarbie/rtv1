/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 17:28:22 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/25 11:01:37 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cast_nbr(char *str)
{
	int res;

	res = 0;
	while (*str && (*str >= '0') && (*str <= '9'))
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res);
}

int			ft_atoi(const char *str)
{
	char *ps;

	ps = (char *)str;
	if (ps == NULL)
		return (0);
	while (*ps && (*ps == ' ' || *ps == '\t' || *ps == '\n' || *ps == '\v' ||
			*ps == '\f' || *ps == '\r'))
		ps++;
	if (*ps && *ps >= '0' && *ps <= '9')
		return (ft_cast_nbr(ps));
	else if (*ps && *ps == '+')
		return (ft_cast_nbr(++ps));
	else if (*ps && *ps == '-')
		return (ft_cast_nbr(++ps) * -1);
	else
		return (0);
}
