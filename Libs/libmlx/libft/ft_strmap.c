/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:35:32 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/24 16:56:42 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*s2;

	i = 0;
	s2 = NULL;
	if (s && f)
	{
		s2 = ft_strnew(ft_strlen(s));
		if (!s2)
			return (NULL);
		while (s[i])
		{
			s2[i] = f(s[i]);
			i++;
		}
	}
	return (s2);
}
