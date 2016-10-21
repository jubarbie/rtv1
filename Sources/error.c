/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 14:55:18 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/21 19:40:17 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		quit_rt(t_env *e)
{
	free_env(e);
	exit(EXIT_FAILURE);
	return (0);
}

void	error_file(t_env *e)
{
	ft_putstr("Wrong file format\n");
	quit_rt(e);
}

void	error_usage(void)
{
	ft_putstr("usage: ./rtv1\n");
	exit(EXIT_FAILURE);
}

void	error_opt(char opt)
{
	ft_putstr("./rtv1: illegal option -- ");
	ft_putchar(opt);
	ft_putchar('\n');
	error_usage();
}
