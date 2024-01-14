/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:51:56 by btan              #+#    #+#             */
/*   Updated: 2024/01/15 00:26:16 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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

// void	interpolate(t_props *props)
// {
// 	t_color	*color;
// 	t_color	*step;

// 	color = dec_to_rgb(props->pixel.color);
// 	step = ft_calloc(1, sizeof(t_color));
//     // ft_printf("here");
// 	step = color_step(dec_to_rgb(props->pixel.color), dec_to_rgb(props->pixel.next_color), pixels_per_unit(props));
// 	color->red += step->red;
// 	color->green += step->green;
// 	color->blue += step->blue;
// 	props->pixel.color = rgb_to_dec(color);
// 	free(color);
// 	free(step);
// }

static void    step_color(t_color *color, t_color *step)
{
    color->red += step->red;
    color->green += step->green;
    color->blue += step->blue;
}

static void check_slope(int *axis, int *iter)
{
    *iter = -1;
    if (*axis < 0)
        *axis = -(*axis);
    else
        *iter = 1;
}

void draw_bresenham_low(t_line *line, t_props *props)
{
    int dx;
    int dy;
    int yi;
    int diff;
    int y;

    dx = line->x1 - line->x0;
    dy = line->y1 - line->y0;
    check_slope(&dy, &yi);
    diff = (2 * dy) - dx;
    y = line->y0;
    while (line->x0 <= line->x1)
    {
        draw_pixel(line->x0, y, props);
        if (diff > 0)
        {
            y = y + yi;
            diff = diff - (2 * dx);
        }
        diff = diff + (2 * dy);
        line->x0++;
    }
}

void draw_bresenham_high(t_line *line, t_props *props)
{
    int dx;
    int dy;
    int xi;
    int diff;
    int x;

    dx = line->x1 - line->x0;
    dy = line->y1 - line->y0;
    check_slope(&dx, &xi);
    diff = 2 * dx - dy;
    x = line->x0;
    while (line->y0 <= line->y1)
    {
        draw_pixel(x, line->y0, props);
        if (diff > 0)
        {
            x = x + xi;
            diff = diff - (2 * dy);
        }
        diff = diff + (2 * dx);
        line->y0++;
    }
}

static void	ft_swap(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void draw_bresenham(t_line *line, t_props *props)
{
    int dx, dy;

    dx = line->x1 - line->x0;
    dy = line->y1 - line->y0;
    if (ABS(dy) < ABS(dx))
    {
        if (line->x0 > line->x1)
        {
            ft_swap(&line->x0, &line->x1);
            ft_swap(&line->y0, &line->y1);
        }
        draw_bresenham_low(line, props);
    }
    else
    {
        if (line->y0 > line->y1)
        {
            ft_swap(&line->x0, &line->x1);
            ft_swap(&line->y0, &line->y1);
        }
        draw_bresenham_high(line, props);
    }
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

void    draw_background(t_props *props)
{
    int x;
    int y;

    y = 0;
    while (y++ < props->height)
    {
        x = 0;
        while (x < props->width)
            draw_pixel(++x, y, props);
    }
}