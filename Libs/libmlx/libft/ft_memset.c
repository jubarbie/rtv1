/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 09:35:47 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/19 10:16:47 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	cc;
	char			*pb;

	cc = (char)c;
	pb = (char *)b;
	while (len-- != 0)
		*(pb++) = c;
	return (b);
}
