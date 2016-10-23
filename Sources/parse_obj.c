/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 11:04:38 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/23 13:22:35 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	*get_obj_param(t_env *e, int *nb, char *str)
{
	char	**tab;
	double	*param;
	int		i;

	tab = ft_strsplit(str, ' ');
	i = 0;
	while (tab[i])
		i++;
	if (!(param = malloc(sizeof(double) * i - 1)))
		error_perso(e, "malloc (t_param *param) failed in get_obj_param()");
	i = 0;
	while (tab[i])
	{
		param[i] = atof(tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
	*nb = i;
	return (param);
}

static char		*get_obj_type(t_env *e, char *str, int n)
{
	char	**obj;
	char	*ret;
	int		i;

	obj = ft_strsplit(OBJ_ALLOWED, ' ');
	i = 0;
	while (obj[i] && !(ft_strnstr(str, obj[i], n)))
		i++;
	if (!obj[i])
		error_perso(e, "oject type is not supported");
	else
	{
		ret = ft_strdup(obj[i]);
		i = -1;
		while (obj[++i])
			free(obj[i]);
		free(obj);
		return (ret);
	}
	return (0);
}

static int		get_obj_color(t_env *e, char *str, int n)
{
	char	*tmp;
	char	*color_h;
	char	*color_i;
	int		color;

	color_h = NULL;
	if (!(tmp = ft_strnstr(str, "color {", n)))
		return (0);
	if ((tmp = ft_strnstr(tmp + 7, "rgb {", size_to_end_acc(e, tmp + 7))))
		color_h = get_in_acc(e, tmp, "rgb {", n);
	color_i = ft_convert_base(color_h + 2, "0123456789ABCDEF", "0123456789");
	color = ft_atoi(color_i);
	free(color_i);
	free(color_h);
	return (color);
}

void			build_object(t_env *e, char *str, int n)
{
	t_object	obj;
	t_list		*elem;
	char		*name;
	char		*tmp;

	name = get_in_acc(e, str, "name {", size_to_end_acc(e, str));
	if (!(tmp = ft_strnstr(str, "inter {", n)))
		error_file(e);
	obj.type = get_obj_type(e, tmp + 7, size_to_end_acc(e, tmp + 7));
	obj.name = ft_strdup(name);
	obj.pos = get_origin(tmp + 7, size_to_end_acc(e, tmp + 7));
	tmp = get_in_acc(e, tmp + 7, obj.type, size_to_end_acc(e, tmp + 7));
	obj.param = get_obj_param(e, &(obj.nb_param), tmp);
	obj.color = get_obj_color(e, str, n);
	elem = ft_lstnew(&obj, sizeof(obj));
	ft_lstadd(&(e->scene->obj), elem);
	free(name);
	free(tmp);
}
