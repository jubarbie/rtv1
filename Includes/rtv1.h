/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 13:04:37 by jubarbie          #+#    #+#             */
/*   Updated: 2016/10/20 12:47:13 by jubarbie         ###   ########.fr       */
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
# define NB_TH 5

# define OPT_REF "d"
# define OPT e->opt
# define D (OPT & (1 << 0))

# define OBJ "sphere plane cube cone cylinder"

# define MLX e->mlx
# define WIN e->win
# define WIN_WIDTH e->win_width
# define WIN_HEIGHT e->win_height
# define BPP e->bpp
# define SIZELINE e->sizeline
# define ENDIAN e->endian
# define IMG e->img
# define IMG_ADDR e->img_addr

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
	t_vector	*pos;
	double		*param;
	int			nb_param;
	int			color;
}				t_object;

typedef struct	s_scene
{
	char		*name;
	t_vector	*cam_pos;
	t_vector	*cam_dir;
	t_list		*obj;
}				t_scene;

typedef struct	s_env
{
	char		opt;
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	int			bpp;
	int			sizeline;
	int			endian;
	void		*img;
	char		*img_addr;

	t_scene		*scene;
}				t_env;

int				get_options(int ac, char **av, char *opt);

t_env			*init_env(int size_x, int size_y);
void			free_env(t_env *e);

void			parse_rt(t_env *e, char *file_name);
void			build_object(t_env *e, char *str, int n);
char			*get_in_acc(t_env *e, char *str, char *acc, int n);
t_vector		*get_origin(char *str, int n);
int				size_to_end_acc(char *str);

void			img_put_pixel(t_env *e, int x, int y, unsigned int color);

t_vector		*new_vector(double x, double y, double z);
void			rot_vector(t_vector *v, double angle);
void			add_vectors(t_vector *v1, t_vector *v2);
void			sub_vectors(t_vector *v1, t_vector *v2);
void			time_vector(t_vector *v, double i);

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
