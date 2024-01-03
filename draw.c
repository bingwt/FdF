/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:51:56 by btan              #+#    #+#             */
/*   Updated: 2024/01/04 03:08:10 by btan             ###   ########.fr       */
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

void	draw_line(int x0, int y0, int x1, int y1, t_props props)
{
	int	dx;
	int	dy;
	int	D;
	int	x;
	int	y; 

	dx = x1 - x0;
	dy = y1 - y0;
	D = 2*dy - dx;
	x = x0;
	y = y0;

	while (x <= x1)
	{
		draw_pixel(x, y, props);
		if (D > 0)
		{
			y = y + 1;
			D = D - 2*dx;
		}
		D = D + 2*dy;
		x++;
	}
}
