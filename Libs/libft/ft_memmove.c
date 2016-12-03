/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 10:48:45 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/03 18:09:00 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*ptrs;
	char		*ptrd;

	ptrs = (const char *)src;
	ptrd = (char *)dst;
	if (dst <= src)
		return (ft_memcpy(dst, src, len));
	ptrs += len;
	ptrd += len;
	while (len-- != 0)
		*--ptrd = *--ptrs;
	return (dst);
}
