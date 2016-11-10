/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:57:53 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/10 10:24:59 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*s3;

	s3 = NULL;
	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		s3 = ft_strnew(len);
		if (s3 == NULL)
			return (NULL);
		s3 = ft_strcpy(s3, s1);
		s3 = ft_strcat(s3, s2);
	}
	return (s3);
}
