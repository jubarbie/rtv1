/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 10:15:49 by jubarbie          #+#    #+#             */
/*   Updated: 2016/02/26 16:35:18 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_sqrt_up(unsigned int n)
{
	unsigned int ret;

	ret = 0;
	while (ret * ret < n)
		ret++;
	return (ret);
}
