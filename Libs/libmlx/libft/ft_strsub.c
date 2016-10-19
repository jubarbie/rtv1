/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:53:18 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/25 10:59:21 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	s2 = NULL;
	if (s)
	{
		s2 = ft_strnew(len);
		if (s2 == NULL)
			return (NULL);
		s2 = ft_strncpy(s2, &(s[start]), len);
	}
	return (s2);
}
