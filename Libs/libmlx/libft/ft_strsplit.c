/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 19:23:41 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/25 11:04:33 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static size_t	word_len(char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s++ != c)
		len++;
	return (len);
}

static size_t	count_words(char *s, char c)
{
	size_t i;

	i = 0;
	if (s)
		while (*s)
		{
			if (*s != c)
			{
				i++;
				s += word_len(s, c) - 1;
			}
			s++;
		}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	char	**tab;
	size_t	w_len;

	tab = NULL;
	i = count_words((char*)s, c);
	tab = (char **)ft_memalloc(sizeof(char *) * i + 1);
	tab[i] = NULL;
	i = 0;
	if (s)
		while (*s)
		{
			if (*s != c)
			{
				w_len = word_len((char *)s, c);
				tab[i] = ft_strnew(w_len);
				if (tab[i] == NULL)
					return (NULL);
				tab[i] = ft_strncpy(tab[i], s, w_len);
				s += (w_len - 1);
				i++;
			}
			s++;
		}
	return (tab);
}
