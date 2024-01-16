/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:51:56 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 09:52:38 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	step_color(t_props *props)
{
	t_color	*current_color;
	current_color = dec_to_rgb(props->pixel.color);
	current_color->red += props->pixel.step->red;
	current_color->green += props->pixel.step->green;
	current_color->blue += props->pixel.step->blue;
	props->pixel.color = rgb_to_dec(current_color);
	free(current_color);
}

static void	check_slope(int *axis, int *iter)
{
	*iter = -1;
	if (*axis < 0)
		*axis = -(*axis);
	else
		*iter = 1;
}

static void	draw_bresenham_low(t_line *line, t_props *props)
{
	int	dx;
	int	dy;
	int	yi;
	int	diff;
	int	y;

	dx = line->x1 - line->x0;
	dy = line->y1 - line->y0;
	check_slope(&dy, &yi);
	diff = (2 * dy) - dx;
	y = line->y0;
	while (line->x0 <= line->x1)
	{
		step_color(props);
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

static void	draw_bresenham_high(t_line *line, t_props *props)
{
	int	dx;
	int	dy;
	int	xi;
	int	diff;
	int	x;

	dx = line->x1 - line->x0;
	dy = line->y1 - line->y0;
	check_slope(&dx, &xi);
	diff = 2 * dx - dy;
	x = line->x0;
	while (line->y0 <= line->y1)
	{
		step_color(props);
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

void	draw_bresenham(t_line *line, t_props *props)
{
	int	dx;
	int	dy;

	dx = line->x1 - line->x0;
	dy = line->y1 - line->y0;
	if (ft_abs(dy) < ft_abs(dx))
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
