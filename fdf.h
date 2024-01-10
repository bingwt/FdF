/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:38 by btan              #+#    #+#             */
/*   Updated: 2024/01/11 00:28:45 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>

# define ABS(Value) (Value < 0 ?  -Value : Value)

# ifndef WIDTH
#  define WIDTH 1024
# endif

# ifndef HEIGHT
#  define HEIGHT 1024
# endif

# ifndef SCALE
#  define SCALE 0.8
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

typedef struct s_pixel
{
	int	x;
	int	y;
	int	color;
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
	void	*mlx;
	void	*window;
	void	*image;
	void	*background;
	int		width;
	int		height;
	int		help;
	t_pixel	pixel;
	t_img	img;
	t_map	map;
}	t_props;

typedef struct	s_data
{
	t_map	map;
}	t_data;

int		is_sep(char const c, char sep);
int		count_words(char const *str, char sep);

float	**vec3_to_matrix(t_vec3 *vec);
float	**matrix_mult(float **a, float **b);
// void	show_matrix(float **matrix);

void	read_map(char *file, t_map *map);
void	init_matrix(char *file, t_map *map);
// void	init_matrix(char *file, t_map *map, t_vec3 **points);

void	draw_pixel(int x, int y, t_props *props);
void	fill_pixels(t_props *props);
void	draw_bresenham(t_line *line, t_props *props);
void	draw_xiaolin_wu(t_line *line, t_props *props);

void	render_pixel(int x, int y, t_props *props);
void	render_line(char *algo, t_line *line, t_props *props);

int		handle_events(t_props *props);

#endif
