/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 06:54:44 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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

void	set_scale(float	***matrix, float scale)
{
	(*matrix)[0][0] *= scale;
	(*matrix)[1][0] *= scale;
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

int	main(int argc, char **argv)
{
	t_map		map;
	t_map		color_map;
	t_props		props;

	read_map(argv[1], &map);
	read_map(argv[1], &color_map);
	props.points = ft_calloc((map.rows * map.cols) + 1, sizeof(t_vec2));
	init_matrix(argv[1], &map, 0);
	init_matrix(argv[1], &color_map, 1);
	props.map = map;
	props.color_map = color_map;
	props.scale = ft_atoi(argv[2]) / 100.0;
	props.rotation = ft_calloc(1, sizeof(t_vec3));
	props.rotation->x = ft_atoi(argv[3]);
	props.rotation->y = ft_atoi(argv[4]);
	props.rotation->z = ft_atoi(argv[5]);
	init_window(&props);
	handle_events(&props);
	props.pixel.color = 0x333333;
	draw_background(&props);
	plot_vectors(&props);
	connect_points(&props);
	mlx_loop(props.mlx);
	return (0);
}
