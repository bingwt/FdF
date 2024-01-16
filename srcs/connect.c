/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:31:18 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 13:05:38 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	connect_col(t_props *props, int row, int col)
{
	t_line	line;

	line.x0 = props->points[(row * props->map.cols) + col]->x;
	line.y0 = props->points[(row * props->map.cols) + col]->y;
	line.x1 = props->points[(row * props->map.cols) + col + 1]->x;
	line.y1 = props->points[(row * props->map.cols) + col + 1]->y;
	props->pixel.color = props->color_map.matrix[row][col];
	draw_bresenham(&line, props);
}

static void	connect_row(t_props *props, int row, int col)
{
	t_line	line;

	line.x0 = props->points[(row * props->map.cols) + col]->x;
	line.y0 = props->points[(row * props->map.cols) + col]->y;
	line.x1 = props->points[(row + 1) * props->map.cols + col]->x;
	line.y1 = props->points[(row + 1) * props->map.cols + col]->y;
	props->pixel.color = props->color_map.matrix[row][col];
	draw_bresenham(&line, props);
}

void	connect_points(t_props *props)
{
	int		row;
	int		col;

	row = 0;
	while (row < props->map.rows)
	{
		col = 0;
		while (col < props->map.cols)
		{
			if (col + 1 < props->map.cols)
				connect_col(props, row, col);
			if (row + 1 < props->map.rows)
				connect_row(props, row, col);
			free(props->points[row * props->map.cols + col]);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}
