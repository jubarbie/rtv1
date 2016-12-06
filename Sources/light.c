/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 08:30:59 by jubarbie          #+#    #+#             */
/*   Updated: 2016/12/06 08:08:19 by jubarbie         ###   ########.fr       */
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

static void	get_v(t_param *param, t_hsv *hsv)
{
	double	angle_light;
	//float	angle_view;
	double	dist;

	(*(param->e->obj_fct_norm[VW_RAY.obj->type]))(&VW_RAY);
	angle_light = cos_v3d(PHO_RAY.dir, VW_RAY.norm);
	//angle_view = cos_v3d(VW_RAY.dir, VW_RAY.norm);
	if (angle_light <= 0)
	{
		hsv->v -= angle_light * 0.18;
		hsv->v = fmax(0.12, hsv->v);
		//hsv->s += pow((angle_light - angle_view), 2.0);
		if (PHO_RAY.obj && PHO_RAY.obj != VW_RAY.obj
			&& PHO_RAY.dist < length_v3d(sub_v3d(VW_RAY.inter, PHO_RAY.pos)) && PHO_RAY.dist > 0)
		{
			dist = length_v3d(sub_v3d(PHO_RAY.inter, VW_RAY.inter));
			hsv->v = fmax(0.12, hsv->v - 0.1);
			//hsv->v -= PHO_RAY.det * dist * 0.5;
		}
	}
}

void		apply_light(t_env *e, t_param *param)
{
	t_list		*lst_light;
	t_object	*light;
	t_list		*lst_obj;
	t_object	*obj;
	t_hsv		hsv;
	double		vm;

	rgb_to_hsv(VW_RAY.obj->color, &hsv.h, &hsv.s, &hsv.v);
	vm = hsv.v;
	hsv.v = 0.12;
	lst_light = e->scene->light;
	while (lst_light)
	{
		light = (t_object *)lst_light->content;
		lst_obj = e->scene->obj;
		init_light_ray(param, light);
		while (lst_obj)
		{
			obj = (t_object *)lst_obj->content;
			if (obj != VW_RAY.obj)
				(*(e->obj_fct_obj[obj->type]))(obj, &PHO_RAY);
			lst_obj = lst_obj->next;
		}
		PHO_RAY.inter = add_v3d(PHO_RAY.pos, smul_v3d(PHO_RAY.dir, PHO_RAY.dist));
		get_v(param, &hsv);
		lst_light = lst_light->next;
	}
	COLOR = hsv_to_rgb(hsv.h, hsv.s, 0.02 + (hsv.v * vm));
}
