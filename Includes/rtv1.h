/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 13:04:37 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/30 17:52:13 by jubarbie         ###   ########.fr       */
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
# define DIST_MAX 100000.0

# define OPT_REF "dl"
# define OPT e->opt
# define D (OPT & (1 << 0))
# define L (OPT & (1 << 1))

# define MOVES e->moves
# define M_FORWARD (1 << 0)
# define M_BACKWARD (1 << 1)
# define M_LEFT (1 << 2)
# define M_RIGHT (1 << 3)
# define M_UP (1 << 4)
# define M_DOWN (1 << 5)

# define OBJ_ALLOWED "light sphere plane cube cone cylinder"
# define NB_OBJ_FCT 6

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
# define X param->x
# define Y param->y
# define VW_RAY param->vw_ray
# define PHO_RAY param->light_ray
# define COLOR param->color

# define VW_WIDTH e->scene->view_plane_width
# define VW_HEIGHT e->scene->view_plane_height
# define VW_DIST e->scene->view_plane_dist
# define VW_UP_LEFT e->scene->view_plane_up_left
# define CAM_POS e->scene->cam_pos
# define CAM_DIR e->scene->cam_dir
# define CAM_UP e->scene->cam_up
# define CAM_RIGHT e->scene->cam_right
# define GAP_X e->scene->gap_x
# define GAP_Y e->scene->gap_y

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

typedef struct	s_ray
{
	t_vector	pos;
	t_vector	dir;
	t_vector	inter;
	double		dist;
	t_object	*obj;
}				t_ray;

typedef struct	s_scene
{
	char		*name;
	t_vector	cam_pos;
	t_vector	cam_dir;
	t_vector	cam_up;
	t_vector	cam_right;
	t_list		*obj;
	t_list		*light;
	double		view_plane_width;
	double		view_plane_height;
	double		view_plane_dist;
	t_vector	view_plane_up_left;
	double		gap_x;
	double		gap_y;
}				t_scene;

typedef struct	s_param
{
	struct s_env	*e;
	int				index;
	int				x;
	int				y;
	t_ray			vw_ray;
	t_ray			light_ray;
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
	char		moves;
	t_scene		*scene;
	void		(*obj_fct[NB_OBJ_FCT])(t_object *, t_ray *);
	t_param		*param[NB_TH];
}				t_env;

int				get_options(int ac, char **av, char *opt);

t_env			*init_env(char *file_name, char opt);
void			free_env(t_env *e);

void			parse_rt(t_env *e, char *file_name);
void			build_object(t_env *e, char *str, int n);
char			*get_in_acc(t_env *e, char *str, char *acc, int n);
t_vector		get_origin(char *str, int n);
int				size_to_end_acc(t_env *e, char *str);

int				create_img(t_env *e);
void			img_put_pixel(t_env *e, int x, int y, unsigned int color);
int				moves(t_env *e);

void			print_vector(t_vector v, char *str);
t_vector		*new_vector(double x, double y, double z);
t_vector		fill_vector(double x, double y, double z);
void			rot_vector(t_vector v, double angle);
t_vector		add_vectors(t_vector v1, t_vector v2);
t_vector		sub_vectors(t_vector v1, t_vector v2);
t_vector		time_vector(t_vector v, double i);
double			norm_vector(t_vector v);
t_vector		unit_vector(t_vector v);
double			angle_vectors(t_vector v1, t_vector v2);
t_vector		perp_vector(t_vector v1, t_vector v2);

void			*raytracer(void *arg);
void			sphere(t_object *obj, t_ray *ray);
void			plane(t_object *obj, t_ray *ray);
void			cylinder(t_object *obj, t_ray *ray);

void			error_usage(void);
void			error_file(t_env *e);
void			error_opt(char opt);
void			error_perso(t_env *e, char *str);
int				quit_rt(t_env *e);
void			debug(t_env *e);

unsigned int	hsv_to_rgb(unsigned int h, double s, double v);
void			rgb_to_hsv(unsigned int rgb, int *h, double *s, double *v);
int				add_color(int c1, int c2);

int				ft_key_press(int keycode, t_env *e);
int				ft_key_release(int keycode, t_env *e);

#endif
