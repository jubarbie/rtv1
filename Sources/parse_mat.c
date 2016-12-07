/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 11:04:38 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/07 16:29:28 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			add_mat(t_env *e, t_object *obj, char *str, int n)
{
	char	*tmp;
	char	*mat;

	obj->mat.shine = 0;
	obj->mat.diffuse = 0.5;
	if ((tmp = ft_strnstr(str, "mat {", n)))
	{
		mat = get_in_acc(e, tmp, "mat {", n);
		if ((tmp = ft_strnstr(mat, "diffuse {", n)))
			obj->mat.diffuse = ft_atof(get_in_acc(e, tmp, "diffuse {", n));
		if ((tmp = ft_strnstr(mat, "shine {", n)))
			obj->mat.shine = ft_atof(get_in_acc(e, tmp, "shine {", n));
		free(mat);
	}
}
