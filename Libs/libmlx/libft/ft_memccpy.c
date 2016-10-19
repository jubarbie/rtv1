/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 10:18:18 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/25 12:33:35 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src, int c,
		size_t n)
{
	unsigned char		*ptrd;
	const unsigned char	*ptrs;
	unsigned char		cc;

	ptrs = (const unsigned char *)src;
	ptrd = (unsigned char *)dst;
	cc = (unsigned char)c;
	while (n-- != 0)
	{
		*ptrd = *ptrs;
		if (*ptrs == cc)
			return (++ptrd);
		ptrd++;
		ptrs++;
	}
	return (NULL);
}
