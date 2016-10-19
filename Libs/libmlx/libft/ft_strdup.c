/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 11:35:40 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/19 11:45:39 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*ps2;
	size_t	len;

	len = ft_strlen(s1);
	s2 = malloc(sizeof(char) * len + 1);
	if (s2 == NULL)
		return (NULL);
	ps2 = s2;
	while (len-- != 0)
	{
		*ps2 = *s1;
		s1++;
		ps2++;
	}
	*ps2 = '\0';
	return (s2);
}
