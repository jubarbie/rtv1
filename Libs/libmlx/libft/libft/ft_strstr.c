/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 13:07:48 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/20 19:34:50 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	char		*pos;
	const char	*pl;

	if (!*little)
		return ((char *)big);
	while (*big)
	{
		if (*big == *little)
		{
			pos = (char *)big;
			pl = little;
			while (*big == *pl)
			{
				big++;
				pl++;
				if (*pl == '\0')
					return (pos);
				if (*big == '\0')
					return (NULL);
			}
			big = (const char *)pos;
		}
		big++;
	}
	return (NULL);
}
