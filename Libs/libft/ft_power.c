/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 17:40:48 by jubarbie          #+#    #+#             */
/*   Updated: 2016/03/03 13:08:14 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int n, int power)
{
	int res;

	res = n * n;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (n);
	if (power > 2)
		res = n * (ft_power(n, --power));
	return (res);
}
