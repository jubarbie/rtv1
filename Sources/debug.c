/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 18:49:11 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/20 12:26:14 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	debug(t_env *e)
{
	t_list		*elem;
	t_object	*obj;
	int			i;

	printf("Debug: \n");
	printf("	Scene name: \"%s\"\n", e->scene->name);
	printf("	Camera:\n");
	printf("		origin(%lf, %lf, %lf)\n", e->scene->cam_pos->x, e->scene->cam_pos->y, e->scene->cam_pos->z);
	elem = e->scene->obj;
	printf("	Objects:\n");
	while (elem)
	{
		obj = (t_object *)(elem->content);
		printf("		name: \"%s\"\n", obj->name);
		printf("		type: \"%s\"\n", obj->type);
		printf("		param: \n");
		i = -1;
		while (++i < obj->nb_param)
			printf("			%lf\n", obj->param[i]);
		printf("		origin(%lf, %lf, %lf)\n", obj->pos->x, obj->pos->y, obj->pos->z);
		printf("		color: 0x%08.8X\n", obj->color);
		printf("		----------\n");
		elem = elem->next;
	}
}