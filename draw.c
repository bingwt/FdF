/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:51:56 by btan              #+#    #+#             */
/*   Updated: 2024/01/11 04:44:23 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

// void	draw_pixel(int x, int y, t_props props)
// {
// 	char	*buffer;
// 	int		pixel;
// 	int		pixel_bits;
// 	int		line_bytes;

// 	buffer = mlx_get_data_addr(props->image, &pixel_bits, &line_bytes, &props->img.endian);
// 	props->pixel.color = mlx_get_color_value(props->mlx, props->pixel.color);
// 	pixel = (y * line_bytes) + (x * 4);
// 	if (props->img.endian == 1)
// 	{
// 		buffer[pixel + 0] = (props->pixel.color >> 24);
// 		buffer[pixel + 1] = (props->pixel.color >> 16) & 0xFF;
// 		buffer[pixel + 2] = (props->pixel.color >> 8) & 0xFF;
// 		buffer[pixel + 3] = (props->pixel.color) & 0xFF;
// 	}

// 	else if (props->img.endian == 0)
// 	{
// 		buffer[pixel + 0] = (props->pixel.color) & 0xFF;
// 		buffer[pixel + 1] = (props->pixel.color >> 8) & 0xFF;
// 		buffer[pixel + 2] = (props->pixel.color >> 16) & 0xFF;
// 		buffer[pixel + 3] = (props->pixel.color >> 24);
// 	}
// }

void	draw_pixel(int x, int y, t_props *props)
{
	char	*buffer;
	int		offset;
	int		pixel_bits;
	int		line_bytes;

	pixel_bits = props->img.pixel_bits;
	line_bytes = props->img.line_bytes;
	buffer = mlx_get_data_addr(props->image, &pixel_bits, &line_bytes, &props->img.endian);
	offset = (line_bytes * y) + (x * (pixel_bits / 8));	
	*((unsigned int *)(offset + buffer)) = props->pixel.color;
	//*((unsigned int *)(offset + buffer)) = (props->pixel.alpha << 24) | props->pixel.color;
}

//void	draw_pixel(int x, int y, t_props props)
//{
//	mlx_put_pixel(props->image, x, y, props->pixel.color);
//}

void	fill_pixels(t_props *props)
{
	int	x;
	int	y;

	y = 0;
	while (y++ < props->height)
	{
		x = 0;
		while (x < props->width)
			draw_pixel(++x, y, props);
	}
}

// void	draw_bresenham(t_line *line, t_props *props)
// {
// 	int	dx;
// 	int	dy;
// 	int	d;
// 	int	x;
// 	int	y;

// 	dx = line->x1 - line->x0;
// 	dy = line->y1 - line->y0;
// 	d = 2 * dy - dx;
// 	x = line->x0;
// 	y = line->y0;
// 	while (x <= line->x1)
// 	{
// 		draw_pixel(x, y, props);
// 		if (d > 0)
// 		{
// 			y = y + 1;
// 			d = d - 2 * dx;
// 		}
// 		d = d + 2 * dy;
// 		x++;
// 	}
// }

static void draw_bresenham_low(t_line *line, t_props *props)
{
	int	dx;
	int	dy;
	int	y;
	int	p;

	dx = line->x1 - line->x0;
	dy = line->y1 - line->y0;
	p = 2 * dy - dx;
	y = line->y0;
	while (line->x0 <= line->x1)
	{
		draw_pixel(line->x0, y, props);
		if (p > 0)
		{
			y++;
			p = p - 2 * dx;
		}
		p = p + 2 * dy;
		line->x0++;
	}
}

static void draw_bresenham_high(t_line *line, t_props *props)
{
	int	dx;
	int	dy;
	int	x;
	int	p;

	dx = line->x1 - line->x0;
	dy = line->y1 - line->y0;
	p = 2 * dx - dy;
	x = line->x0;
	while (line->y0 <= line->y1)
	{
		draw_pixel(x, line->y0, props);
		if (p > 0)
		{
			x++;
			p = p - 2 * dy;
		}
		p = p + 2 * dx;
		line->y0++;
	}
}

void draw_bresenham(t_line *line, t_props *props)
{
	if (ABS(line->y1 - line->y0) < ABS(line->x1 - line->x0))
	{
		if (line->x0 > line->x1)
			draw_bresenham_low(line, props);
		else
			draw_bresenham_low(line, props);
	}
	else
	{
		if (line->y0 > line->y1)
			draw_bresenham_high(line, props);
		else
			draw_bresenham_high(line, props);
	}
}

static void	ft_swap(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	draw_xiaolin_wu(t_line *line, t_props *props)
{
    float	dx;
    float	dy;
    float	gradient;
    float	x;
    float	y;

    if (ABS(line->y1 - line->y0) > ABS(line->x1 - line->x0))
    {
        ft_swap(&line->x0, &line->y0);
        ft_swap(&line->x1, &line->y1);
    }
    if (line->x0 > line->x1)
    {
        ft_swap(&line->x0, &line->x1);
        ft_swap(&line->y0, &line->y1);
    }
    dx = line->x1 - line->x0;
    dy = line->y1 - line->y0;
    if (dx == 0) {
	y = line->y0;
	while (y <= line->y1) {
		draw_pixel(line->x0, y, props);
		y++;
	}
    } else {
        gradient = dy / dx;
        y = line->y0 + gradient;
        while (x++ < line->x1)
        {
            draw_pixel(x, y, props);
            draw_pixel(x, (y += gradient) + 1, props);
        }
    }
}
