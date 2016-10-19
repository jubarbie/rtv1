/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 13:07:48 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/20 18:01:32 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		llen;
	size_t		i;

	i = 0;
	llen = ft_strlen(little);
	if (!little)
		return ((char *)big);
	while (*big && (i + llen) <= len)
	{
		if (ft_memcmp(big, little, llen) == 0)
			return ((char *)big);
		big++;
		i++;
	}
	return (NULL);
}
