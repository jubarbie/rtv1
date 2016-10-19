/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 18:49:11 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/19 19:37:13 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	debug(t_env *e)
{
	printf("Debug: \n");
	printf("	Scene name: \"%s\"\n", e->scene->name);
	printf("	Camera:\n");
	printf("		origin(%lf, %lf, %lf)\n", e->scene->cam_pos->x, e->scene->cam_pos->y, e->scene->cam_pos->z);
}
