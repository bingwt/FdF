/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2024/01/11 00:29:41 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	init_window(t_props *props)
{
	props->mlx = mlx_init();
	props->width = WIDTH;
	props->height = HEIGHT;
	props->window = mlx_new_window(props->mlx, props->width, props->height, "FdF");
	props->image = mlx_new_image(props->mlx, props->width, props->height);
	props->background = mlx_new_image(props->mlx, props->width, props->height);
	props->help = 0;
}

static	void show_matrix(t_map *map)
{
	int row;
	int	col;

	row = 0;
	while (row < map->rows)
	{
		col = 0;
		while (col < map->cols)
		{
			ft_printf("%d ", map->matrix[row][col]);
			col++;
		}
		ft_printf("\n");
		row++;
	}
}

static void	draw_scale(t_props *props)
{
	t_line line;

	props->pixel.color = 0xFFFFFF;
	draw_pixel(0, 0, props);
	draw_pixel(256, 256, props);
	draw_pixel(768, 256, props);
	// draw_pixel(512, 512, props);
	draw_pixel(256, 768, props);
	draw_pixel(768, 768, props);
	draw_pixel(1023, 1023, props);
	line.x0 = 0;
	line.y0 = 0;
	line.x1 = 256;
	line.y1 = 256;
	// draw_xiaolin_wu(&line, props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

int	pixel_per_plot(t_props *props)
{
	int		pixel_per_plot;
	int		plot_width;
	int		plot_height;

	plot_width = (props->width * SCALE) / props->map.cols;
	plot_height = (props->height * SCALE) / props->map.rows;
	if (plot_width < plot_height) 
		pixel_per_plot = plot_width;
	else
	pixel_per_plot = plot_height;
	if (pixel_per_plot == 0)
		return (1);
	return (pixel_per_plot);
}

void	plot_points(t_props *props)
{
	int	ppp;
	int	offset_x;
	int	offset_y;
	int	row;
	int	col;
	t_line	line;

	ppp = pixel_per_plot(props);
	offset_x = (WIDTH * SCALE) / 2;
	offset_y = (HEIGHT * SCALE) / 2;
	ft_printf("ppp: %d\n", ppp);
	props->pixel.color = 0xFFFFFF;
	row = 0;
	while (row < props->map.rows)
	{
		col = 0;
		while (col < props->map.cols)
		{
			props->pixel.x = (col * ppp) + (ppp / 2);
			props->pixel.y = (row * ppp) + (ppp / 2);
			if (props->map.matrix[row][col] > 0)
				props->pixel.color = 0x604045;
			else
				props->pixel.color = 0XFFFFFF;
			draw_pixel(props->pixel.x, props->pixel.y, props);
			line.x0 = props->pixel.x;
			line.y0 = props->pixel.y;
			if (col + 1 < props->map.cols)
			{
				line.x1 = ((col + 1) * ppp) + (ppp / 2);
				line.y1 = (row * ppp) + (ppp / 2);
				draw_bresenham(&line, props);
			}
			col++;
		}
		row++;
	}
	
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;
	t_props	props;
	t_line	line;
	t_vec3	*points;

	if (argc != 2)
	{
		ft_printf("Please provide a map!\n");
		return (1);
	}
	read_map(argv[1], &map);
	points = ft_calloc((map.rows * map.cols) + 1, sizeof(t_vec3));
	init_matrix(argv[1], &map);
	// init_matrix(argv[1], &map, &points);
	// show_matrix(&map);
	props.map = map;

	init_window(&props);
	// draw_scale(&props);
	plot_points(&props);
	
	
	
	handle_events(&props);
	mlx_loop(props.mlx);
	return (0);
}
