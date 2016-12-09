/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 08:30:59 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/09 18:56:05 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_light_ray(t_param *param, t_object *light)
{
	PHO_RAY.pos = light->pos;
	PHO_RAY.dist = DIST_MAX;
	PHO_RAY.dir = unit_v3d(sub_v3d(VW_RAY.inter, PHO_RAY.pos));
	PHO_RAY.obj = NULL;
}

static void	do_shininess(t_param *param, t_object *light, t_hsv *hsv, t_v3d ref)
{
	int		color;
	double	angle_ref;

	if (VW_RAY.obj->mat.shine > 0.0)
	{
		angle_ref = cos_v3d(ref, VW_RAY.dir);
		if (angle_ref <= -0.95)
		{
			color = hsv_to_rgb(hsv->h, hsv->s, hsv->v);
			color = add_color(color, light->color, ((-0.95 - angle_ref) / 0.05)
													* VW_RAY.obj->mat.shine);
			rgb_to_hsv(color, &hsv->h, &hsv->s, &hsv->v);
		}
	}
}

static void	get_color(t_param *param, t_object *light, t_hsv *hsv)
{
	double	angle_light;
	t_v3d	ref;
	double	dist;

	PHO_RAY.inter = add_v3d(PHO_RAY.pos, smul_v3d(PHO_RAY.dir, PHO_RAY.dist));
	angle_light = cos_v3d(PHO_RAY.dir, VW_RAY.norm);
	ref = sub_v3d(PHO_RAY.dir, smul_v3d(VW_RAY.norm, 2.0 *
				dot_v3d(PHO_RAY.dir, VW_RAY.norm)));
	if (angle_light <= 0.001)
	{
		hsv->v -= angle_light * VW_RAY.obj->mat.diffuse;
		hsv->v = fmax(VW_RAY.obj->mat.diffuse, hsv->v);
		if (PHO_RAY.obj && PHO_RAY.obj != VW_RAY.obj
			&& PHO_RAY.dist < length_v3d(sub_v3d(VW_RAY.inter, PHO_RAY.pos))
			&& PHO_RAY.dist > 0)
		{
			dist = length_v3d(sub_v3d(PHO_RAY.inter, VW_RAY.inter));
			hsv->v = fmax(VW_RAY.obj->mat.diffuse, hsv->v - 0.1);
		}
		do_shininess(param, light, hsv, ref);
	}
}

void		apply_light(t_env *e, t_param *param)
{
	t_list		*lst_light;
	t_list		*lst_obj;
	t_object	*obj;
	t_hsv		hsv;
	double		vm;

	rgb_to_hsv(VW_RAY.obj->color, &hsv.h, &hsv.s, &hsv.v);
	vm = hsv.v;
	hsv.v = VW_RAY.obj->mat.diffuse;
	lst_light = e->scene->light;
	while (lst_light)
	{
		lst_obj = e->scene->obj;
		init_light_ray(param, (t_object *)lst_light->content);
		while (lst_obj)
		{
			obj = (t_object *)lst_obj->content;
			if (obj != VW_RAY.obj)
				(*(e->obj_fct_obj[obj->type]))(obj, &PHO_RAY);
			lst_obj = lst_obj->next;
		}
		get_color(param, (t_object *)lst_light->content, &hsv);
		lst_light = lst_light->next;
	}
	COLOR = hsv_to_rgb(hsv.h, hsv.s, 0.02 + (hsv.v * vm));
}
