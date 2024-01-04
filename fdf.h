/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:38 by btan              #+#    #+#             */
/*   Updated: 2024/01/04 14:12:21 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
#include <stdio.h>
#include <mlx.h>
#include <libft.h>
#include <fcntl.h>

# ifndef WIDTH
#  define WIDTH 960
# endif

# ifndef HEIGHT
#  define HEIGHT 540
# endif


typedef struct s_pixel
{
	int	x;
	int	y;
	int	color;
}	t_pixel;

typedef struct s_image
{
	int	pixel_bits;
	int	line_bytes;
	int	endian;
}	t_img;

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
}	t_props;

typedef struct s_map
{
	int	rows;
}	t_map;

void	read_map(int fd, t_map *map);

int		handle_keydown(int key, t_props *props);
int		handle_mouse(int x, int y, void *mlx_ptr, void *window);
int		handle_close(int key, t_props *props);
int		handle_events(t_props *props);

void	draw_pixel(int x, int y, t_props props);
void	fill_pixels(t_props props);
void	draw_line(int x0, int y0, int x1, int y1, t_props props);

#endif
