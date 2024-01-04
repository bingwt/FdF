/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:51:56 by btan              #+#    #+#             */
/*   Updated: 2024/01/04 22:04:34 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

//void	draw_pixel(t_pixel pix, t_props props, t_img img)
//{
//	char	*buffer;
//	int 	pixel;
//	int		bit;
//
//	buffer = mlx_get_data_addr(props.image, &img.pixel_bits, &img.line_bytes, &img.endian);
//	pix.color = mlx_get_color_value(props.mlx, pix.color);
//	pixel = (pix.y * img.line_bytes) + (pix.x * 4);
//	if (img.endian == 1)
//	{
//		buffer[pixel + 0] = (pix.color >> 24);
//		buffer[pixel + 1] = (pix.color >> 16) & 0xFF;
//		buffer[pixel + 2] = (pix.color >> 8) & 0xFF;
//		buffer[pixel + 3] = (pix.color) & 0xFF;
//	}
//
//	else if (img.endian == 0)
//	{
//		buffer[pixel + 0] = (pix.color) & 0xFF;
//		buffer[pixel + 1] = (pix.color >> 8) & 0xFF;
//		buffer[pixel + 2] = (pix.color >> 16) & 0xFF;
//		buffer[pixel + 3] = (pix.color >> 24);
//	}
//}

void	draw_pixel(int x, int y, t_props props)
{
	char	*buffer;
	int		offset;
	int		pixel_bits;
	int		line_bytes;

	pixel_bits = props.img.pixel_bits;
	line_bytes = props.img.line_bytes;
	buffer = mlx_get_data_addr(props.image, &pixel_bits, &line_bytes, &props.img.endian);
	offset = (line_bytes * y) + (x * (pixel_bits / 8));	
	*((unsigned int *)(offset + buffer)) = props.pixel.color;
	//*((unsigned int *)(offset + buffer)) = (props.pixel.alpha << 24) | props.pixel.color;
}

//void	draw_pixel(int x, int y, t_props props)
//{
//	mlx_put_pixel(props.image, x, y, props.pixel.color);
//}

void	fill_pixels(t_props props)
{
	int	x;
	int	y;

	y = 0;
	while (y++ < props.height)
	{
		x = 0;
		while (x < props.width)
			draw_pixel(++x, y, props);
	}
}

void	draw_bresenham(t_line line, t_props props)
{
	int	dx;
	int	dy;
	int	d;
	int	x;
	int	y;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	d = 2 * dy - dx;
	x = line.x0;
	y = line.y0;
	while (x <= line.x1)
	{
		draw_pixel(x, y, props);
		if (d > 0)
		{
			y = y + 1;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
		x++;
	}
}

static void	ft_swap(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	draw_xiaolin_wu(t_line line, t_props props)
{
	float	dx;
	float	dy;
	float	gradient;
	float	x;
	float	y;

	if (ABS(line.y1 - line.y0) > ABS(line.x1 - line.x0))
	{
		ft_swap(&line.x0, &line.y0);
		ft_swap(&line.x1, &line.y1);
	}
	if (line.x0 > line.x1)
	{
		ft_swap(&line.x0, &line.x1);
		ft_swap(&line.y0, &line.y1);
	}
	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	gradient = dy / dx;
	y = line.y0 + gradient;
	while (x++ < line.x1)
	{
		draw_pixel(x, y, props);
		draw_pixel(x, (y += gradient) + 1, props);
	}
}
