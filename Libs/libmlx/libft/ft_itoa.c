/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 20:38:28 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/25 11:12:18 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(int n)
{
	if (n == 0)
		return (0);
	return (1 + ft_nbrlen(n / 10));
}

static char		*do_itoa(char *str, int n, int len)
{
	char	*ps;
	int		dig;

	ps = str;
	if (n == 0)
		*str = '0';
	if (n < 0)
	{
		*ps++ = '-';
		len--;
		n = n * -1;
	}
	while (len-- > 0)
	{
		dig = n / ft_power(10, len);
		*ps++ = dig + 48;
		n = n % ft_power(10, len);
	}
	return (str);
}

char			*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	str = NULL;
	len = (n < 0) ? ft_nbrlen(n) + 1 : ft_nbrlen(n);
	if (n == -2147483648)
	{
		str = ft_strnew(11);
		if (str == NULL)
			return (NULL);
		str = ft_strcpy(str, "-2147483648");
		return (str);
	}
	else
	{
		str = ft_strnew(len);
		if (str == NULL)
			return (NULL);
	}
	return (do_itoa(str, n, len));
}
