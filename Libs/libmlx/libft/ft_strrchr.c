/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 13:02:25 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/19 13:06:08 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *lst;
	char cc;

	lst = NULL;
	cc = (char)c;
	while (*s)
	{
		if (*s == cc)
			lst = (char *)s;
		s++;
	}
	if (*s == cc)
		lst = (char *)s;
	return (lst);
}
