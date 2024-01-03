/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:38 by btan              #+#    #+#             */
/*   Updated: 2024/01/03 18:53:33 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include <libft.h>

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

typedef struct s_properties {
	void	*mlx;
	void	*window;
	void	*image;
	int		width;
	int		height;
	int		help;
	t_img	img;
}	t_props;

int		handle_keydown(int key, t_props *props);
int		handle_mouse(int x, int y, void *mlx_ptr, void *window);
int		handle_close(int key, t_props *props);
int		handle_events(t_props *props);

void	draw_pixel(t_pixel pix, t_props props, t_img img);
