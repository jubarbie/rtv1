/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 15:09:50 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/26 15:16:06 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_nbrlen(int nb, int base)
{
	int i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}

static int	ft_to_dec(char *nbr, char *base)
{
	int nbr_dec;
	int len_base;
	int len_nbr;
	int i;
	int j;

	len_base = ft_strlen(base);
	len_nbr = ft_strlen(nbr);
	nbr_dec = 0;
	i = -1;
	while (++i < len_nbr)
	{
		j = -1;
		while (++j < len_base)
			if (nbr[i] == base[j])
				nbr_dec = nbr_dec + (j * ft_power(len_base, len_nbr - i - 1));
	}
	return (nbr_dec);
}

char		*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*ret;
	int		nb_dec;
	int		i;
	int		b;
	int		m;

	nb_dec = ft_to_dec(nbr, base_from);
	b = ft_strlen(base_to);
	i = ft_nbrlen(nb_dec, b);
	if ((ret = (char*)malloc(sizeof(char) * i + 1)) == NULL)
		return (NULL);
	while (--i >= 0)
	{
		m = nb_dec % b;
		ret[i] = base_to[m];
		nb_dec /= b;
	}
	ret[ft_nbrlen(ft_to_dec(nbr, base_from), b)] = '\0';
	return (ret);
}
