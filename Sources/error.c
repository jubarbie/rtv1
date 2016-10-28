/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 14:55:18 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/28 14:12:14 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		quit_rt(t_env *e)
{
	ft_putstr("Quiting rtv1\n");
	free_env(e);
	exit(EXIT_SUCCESS);
	return (0);
}

void	error_perso(t_env *e, char *str)
{
	ft_putstr("Error: ");
	ft_putstr(str);
	ft_putchar('\n');
	free(e);
	exit(EXIT_FAILURE);
}

void	error_file(t_env *e)
{
	ft_putstr("Wrong file format\n");
	free(e);
	exit(EXIT_FAILURE);
}

void	error_usage(void)
{
	ft_putstr("usage: ./rtv1 [-");
	ft_putstr(OPT_REF);
	ft_putstr("] file_name\n");
	exit(EXIT_FAILURE);
}

void	error_opt(char opt)
{
	ft_putstr("./rtv1: illegal option -- ");
	ft_putchar(opt);
	ft_putchar('\n');
	error_usage();
}
