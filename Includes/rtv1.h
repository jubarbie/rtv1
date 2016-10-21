/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 13:04:37 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/21 20:24:05 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include </System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h>
# include <OpenCL/opencl.h>
# include <pthread.h>
# include <time.h>
# include "mlx.h"
# include "libft.h"

# define PI 3.141592
# define NB_TH 13

# define OPT_REF "d"
# define OPT e->opt
# define D (OPT & (1 << 0))

# define OBJ_ALLOWED "sphere plane cube cone cylinder"

# define MLX e->mlx
# define WIN e->win
# define WIN_WIDTH 1000
# define WIN_HEIGHT 800
# define BPP e->bpp
# define SIZELINE e->sizeline
# define ENDIAN e->endian
# define IMG e->img
# define IMG_ADDR e->img_addr

# define ENV param->e
# define TH param->index
# define RAY_POS param->ray_pos
# define RAY_DIR param->ray_dir
# define GAP_X param->gap_x
# define GAP_Y param->gap_y
# define X param->x
# define Y param->y
# define COLOR param->color

# define VW_WIDTH e->scene->view_plane_width
# define VW_HEIGHT e->scene->view_plane_height
# define VW_DIST e->scene->view_plane_dist
# define VW_UP_LEFT e->scene->view_plane_up_left
# define CAM_POS e->scene->cam_pos
# define CAM_DIR e->scene->cam_dir
# define CAM_UP e->scene->cam_up
# define CAM_RIGHT e->scene->cam_right
# define OBJ e->scene->obj


typedef	struct	s_hsv
{
	int		h;
	double	s;
	double	v;
}				t_hsv;

typedef	struct	s_pix
{
	int				x;
	int				y;
	unsigned int	color;
}				t_pix;

typedef struct	s_texture
{
	void		*img;
	char		*addr;
	int			bpp;
	int			width;
	int			sizeline;
}				t_tex;

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct	s_object
{
	char		*type;
	char		*name;
	t_vector	pos;
	double		*param;
	int			nb_param;
	int			color;
}				t_object;

typedef struct	s_scene
{
	char		*name;
	t_vector	cam_pos;
	t_vector	cam_dir;
	t_vector	cam_up;
	t_vector	cam_right;
	t_list		*obj;
	double		view_plane_width;
	double		view_plane_height;
	double		view_plane_dist;
	t_vector	view_plane_up_left;
}				t_scene;

typedef struct	s_param
{
	struct s_env	*e;
	int				index;
	int				x;
	int				y;
	double			gap_x;
	double			gap_y;
	t_vector		ray_pos;
	t_vector		ray_dir;
	int				color;
}				t_param;

typedef struct	s_env
{
	char		opt;
	void		*mlx;
	void		*win;
	int			bpp;
	int			sizeline;
	int			endian;
	void		*img;
	char		*img_addr;

	t_scene		*scene;
	t_param		*param[NB_TH];
}				t_env;

int				get_options(int ac, char **av, char *opt);

t_env			*init_env(char *file_name, char opt);
void			free_env(t_env *e);

void			parse_rt(t_env *e, char *file_name);
void			build_object(t_env *e, char *str, int n);
char			*get_in_acc(t_env *e, char *str, char *acc, int n);
t_vector		get_origin(char *str, int n);
int				size_to_end_acc(char *str);

void			img_put_pixel(t_env *e, int x, int y, unsigned int color);

t_vector		*new_vector(double x, double y, double z);
t_vector		fill_vector(double x, double y, double z);
void			rot_vector(t_vector v, double angle);
t_vector		add_vectors(t_vector v1, t_vector v2);
t_vector		sub_vectors(t_vector v1, t_vector v2);
t_vector		time_vector(t_vector v, double i);
double			norm_vector(t_vector v);
t_vector		unit_vector(t_vector v);
t_vector		perp_vector(t_vector v1, t_vector v2);

void			*raytracer(void *arg);
void			sphere(t_param *param, double *arg);

void			error_usage(void);
void			error_file(t_env *e);
void			error_opt(char opt);
int				quit_rt(t_env *e);
void			debug(t_env *e);

unsigned int	hsv_to_rgb(unsigned int h, double s, double v);
void			rgb_to_hsv(unsigned int rgb, int *h, double *s, double *v);

int				ft_key_press(int keycode, t_env *e);
int				ft_key_release(int keycode, t_env *e);

#endif
