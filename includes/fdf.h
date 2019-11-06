/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:39:56 by marvin            #+#    #+#             */
/*   Updated: 2019/11/04 00:34:02 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "buttons.h"
# define HEIGHT		1000
# define WIDTH		1500
# define TAN30		0.577350269
# define COS30		0.866025404
# define SIN30		0.5
# define RAD(Value)	((Value) * 0.0174533)
# define COLOR_BGR	0x000000

typedef enum
{
	tr_rot_X, tr_rot_Y, tr_rot_Z,
	tr_translate_X, tr_translate_Y, tr_translate_Z,
	tr_scale_X, tr_scale_Y, tr_scale_Z, tr_scale_ALL
}				t_transform_type;
typedef enum
{
	m_tr_rotate, m_tr_translate
}				t_mouse_tr;
typedef enum
{
	ISO, Parallel
}				t_projection_type;
typedef struct	s_color
{
	t_uint8	b;
	t_uint8	g;
	t_uint8	r;
	t_uint8	a;
}				t_color;
typedef struct	s_point3d
{
	float	x;
	float	y;
	float	z;
	t_color	color;
}				t_point3d;
typedef struct	s_point2d
{
	int		x;
	int		y;
	t_color	color;
}				t_point2d;
typedef struct	s_transform
{
	t_point3d	rotation;
	t_point3d	translation;
	t_point3d	scale;
}				t_transform;
typedef struct	s_map
{
	int			min_z;
	int			max_z;
	int			w;
	int			h;
	t_color		min_color;
	t_color		max_color;
	t_point3d	**points3d;
}				t_map;
typedef struct s_mouse
{
	t_bool		is_pressed;
	t_point2d	prev;
	t_mouse_tr	tr_type;
}				t_mouse;

typedef struct	s_view
{
	void				*mlx;
	void				*win;
	void				*img;
	t_color				*data_addr;
	float				*zbuff;
	t_projection_type	projection;
	int					bpp;
	int					line_size;
	int					endian;
	t_transform			transform;
	t_transform_type	tr_type;
	t_mouse				mouse;
	t_map				*map;
}				t_view;

int				read_map(char *fname, t_map *map);
void			p3d_rotate(t_point3d *p, float angle, t_transform_type t);
void			p3d_scale(t_point3d *p, float value, t_transform_type t);
void			p3d_translate(t_point3d *p, float value, t_transform_type t);
int				mouse_press(int button, int x, int y, t_view *param);
int				mouse_release(int b, int x, int y, t_view *v);
int				mouse_move(int x, int y, t_view *v);
void			setup_hooks(t_view *v);
int				key_press(int keycode, t_view *v);
void			draw_map(t_view *v);
t_point2d		*iso(t_point3d *p);
t_point2d		project(t_point3d p, t_view *v);
t_view			*new_view(void);
t_color			rand_color();
void			colorize_points(t_map *m);
void			calc_pixel_color(t_point2d st_p, t_point2d end_p,
													t_point2d *cur_p);
#endif
