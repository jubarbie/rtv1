/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 11:16:35 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/20 16:46:59 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		cc;
	const unsigned char	*ptrs;

	cc = (unsigned char)c;
	ptrs = (const unsigned char *)s;
	while (n-- != 0)
	{
		if (*ptrs == cc)
			return ((void *)ptrs);
		ptrs++;
	}
	return (NULL);
}
