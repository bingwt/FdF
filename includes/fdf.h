/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:38 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 13:06:57 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>
# include <math.h>

# ifndef WIDTH
#  define WIDTH 1024
# endif

# ifndef HEIGHT
#  define HEIGHT 1024
# endif

# ifndef SCALE
#  define SCALE "75"
# endif

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_color
{
	float	red;
	float	green;
	float	blue;
}	t_color;

typedef struct s_pixel
{
	int		color;
	int		next_color;
	t_color	*step;
}	t_pixel;

typedef struct s_line
{
	float	x0;
	float	y0;
	float	x1;
	float	y1;
}	t_line;

typedef struct s_image
{
	int	pixel_bits;
	int	line_bytes;
	int	endian;
}	t_img;

typedef struct s_map
{
	int		rows;
	int		cols;
	int		**matrix;
}	t_map;

typedef struct s_properties
{
	void		*mlx;
	void		*window;
	void		*image;
	int			width;
	int			height;
	int			help;
	t_pixel		pixel;
	t_img		img;
	t_map		map;
	t_map		color_map;
	t_vec2		**points;
	float		scale;
	t_vec3		*rotation;
}	t_props;

int		is_sep(char const c, char sep);
int		count_words(char const *str, char sep);
int		ft_abs(int n);
void	ft_swap(float *a, float *b);
int		ft_atoi_base(const char *str, const char *base);

void	set_local_origin(t_props *props, t_vec3 **vec3);
void	set_world_origin(float ***matrix);

float	**vec3_to_matrix(t_vec3 *vec);
t_vec2	*matrix_to_vec2(float **matrix);
float	**matrix_mult(float **a, float **b);
void	free_matrix(float **matrix);

float	**orthographic(void);
void	rotate_z(float ***matrix, float degrees);
void	rotate_x(float ***matrix, float degrees);
void	rotate_y(float ***matrix, float degrees);
void	rotate_xyz(float ***projection, t_vec3 **rotation);

int		pixels_per_unit(t_props *props);
void	set_scale(float ***matrix, float scale);

void	read_map(char *file, t_map *map);
void	init_matrix(char *file, t_map *map, int color);

void	draw_pixel(int x, int y, t_props *props);
t_color	*hex_to_rgb(char *hex);
t_color	*dec_to_rgb(int dec);
int		rgb_to_dec(t_color *color);
t_color	*color_step(int color1, int color2, int ppu);

void	plot_vectors(t_props *props);
void	connect_points(t_props *props);

void	draw_bresenham(t_line *line, t_props *props);
void	draw_background(t_props *props);

void	handle_events(t_props *props);

#endif
