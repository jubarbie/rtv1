/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 13:00:02 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/19 13:06:38 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	char	*ps1;

	ps1 = s1;
	while (*ps1)
		ps1++;
	while (n-- != 0)
	{
		*ps1 = *s2;
		ps1++;
		s2++;
	}
	*ps1 = '\0';
	return (s1);
}
