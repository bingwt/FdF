/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 13:13:53 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_window(t_props *props)
{
	props->mlx = mlx_init();
	props->width = WIDTH;
	props->height = HEIGHT;
	props->window = mlx_new_window(props->mlx, props->width, \
	props->height, "FdF");
	props->image = mlx_new_image(props->mlx, props->width, props->height);
	props->help = 0;
}

void	draw_background(t_props *props)
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

int	pixels_per_unit(t_props *props)
{
	int	pixels;

	if (WIDTH / props->map.cols > HEIGHT / props->map.rows)
		pixels = HEIGHT / props->map.rows;
	else
		pixels = WIDTH / props->map.cols;
	return (pixels);
}

void	init_props(char **argv, t_props *props)
{
	t_map	map;
	t_map	color_map;

	read_map(argv[1], &map);
	read_map(argv[1], &color_map);
	props->points = ft_calloc((map.rows * map.cols) + 1, sizeof(t_vec2));
	init_matrix(argv[1], &map, 0);
	init_matrix(argv[1], &color_map, 1);
	props->map = map;
	props->color_map = color_map;
	props->scale = ft_atoi(SCALE) / 100.0;
	props->rotation = ft_calloc(1, sizeof(t_vec3));
	props->rotation->x = atan(sqrt(2)) * (180 / M_PI);
	props->rotation->y = 0;
	props->rotation->z = 45;
}

int	main(int argc, char **argv)
{
	t_props		props;

	if (argc != 2)
		handle_error("Only provide 1 additional arguments Example: ./fdf 42.fdf"\
				, "INVALID_INPUT");
	init_props(argv, &props);
	init_window(&props);
	handle_events(&props);
	props.pixel.color = 0x333333;
	draw_background(&props);
	plot_vectors(&props);
	connect_points(&props);
	mlx_loop(props.mlx);
	return (0);
}
