/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 19:07:42 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/25 11:00:31 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlenw(const char *s)
{
	size_t	len;

	len = ft_strlen(s);
	while (s[len - 1] && (s[len - 1] == ' ' || s[len - 1] == '\t' ||
				s[len - 1] == '\n') && len > 0)
		len--;
	return (len);
}

char			*ft_strtrim(char const *s)
{
	char	*ret;
	size_t	size;

	ret = NULL;
	if (s)
	{
		while (*s && (*s == ' ' || *s == '\t' || *s == '\n'))
			s++;
		size = ft_strlenw(s);
		ret = ft_strnew(size);
		if (ret == NULL)
			return (NULL);
		ret = ft_strncpy(ret, s, size);
	}
	return (ret);
}
