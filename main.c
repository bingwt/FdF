/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2024/01/14 23:28:53 by btan             ###   ########.fr       */
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
	props->help = 0;
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
}

void	plot_vectors(t_props *props, int rot_x, int rot_y, int rot_z)
{
	int	row;
	int	col;
	t_vec3	*vec3;
	float	**transformation;
	float	**matrix;
	float	**projection;

	transformation = ortho_view();
	row = 0;
	while (row < props->map.rows)
	{
		col = 0;
		while (col < props->map.cols)
		{
			vec3 = ft_calloc(1, sizeof(t_vec3));
			vec3->x = col;
			vec3->y = row;
			vec3->z = props->map.matrix[row][col];
			set_local_origin(props, &vec3);
			matrix = vec3_to_matrix(vec3);
			projection = matrix_mult(transformation, matrix);
			for (int i = 0; i < 3; i++) {
				free(matrix[i]);
			}
			free(matrix);
			free(vec3);
			rotate_z(&projection, rot_z);
			rotate_x(&projection, rot_x);
			rotate_y(&projection, rot_y);
			set_scale(&projection, pixels_per_unit(props) * props->scale);
			set_world_origin(props, &projection);
			props->points[row * props->map.cols + col] = matrix_to_vec2(projection);
			if (projection[0][0] >= 0 && projection[0][0] < props->width && projection[1][0] >= 0 && projection[1][0] < props->height)
			{
				props->pixel.color = props->color_map.matrix[row][col];
				draw_pixel(projection[0][0], projection[1][0], props);
			}
			for (int i = 0; i < 3; i++) {
				free(projection[i]);
			}
			free(projection);
			col++;
		}
		row++;
	}
		for (int i = 0; i < 3; i++) {
    		free(transformation[i]);
	}
	free(transformation);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

void	print_points(t_props *props)
{
	int	i;

	i = 0;
	while (props->points[i])
	{
		ft_printf("%d: ", i);
		ft_printf("x: %d, y: %d", props->points[i]->x, props->points[i]->y);
		i++;
	}
}

void	connect_points(t_props *props)
{
	int	row;
	int	col;
	t_line	line;

	row = 0;
	while (row < props->map.rows)
	{
		col = 0;
		while (col < props->map.cols)
		{
			if (col + 1 < props->map.cols)
			{
				line.x0 = props->points[(row * props->map.cols) + col]->x;
				line.y0 = props->points[(row * props->map.cols) + col]->y;
				line.x1 = props->points[(row * props->map.cols) + col + 1]->x;
				line.y1 = props->points[(row * props->map.cols) + col + 1]->y;
				props->pixel.color = props->color_map.matrix[row][col];
				props->pixel.next_color = props->color_map.matrix[row][col + 1];
				// interpolate(props, row, col);
				draw_bresenham(&line, props);
				// mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);

			}
			if (row + 1 < props->map.rows)
			{
				line.x0 = props->points[row * props->map.cols + col]->x;
				line.y0 = props->points[row * props->map.cols + col]->y;
				line.x1 = props->points[(row + 1) * props->map.cols + col]->x;
				line.y1 = props->points[(row + 1) * props->map.cols + col]->y;
				props->pixel.color = props->color_map.matrix[row][col];
				props->pixel.next_color = props->color_map.matrix[row + 1][col];
				// interpolate(props, row, col);
				draw_bresenham(&line, props);
				// mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);

			}
			free(props->points[row * props->map.cols + col]);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

void	spin(t_props *props)
{
	int	rot_x;
	int	rot_y;
	int	rot_z;

	rot_x = 0;
	rot_y = 0;
	rot_z = 0;
	plot_vectors(props, 0, 0, 0);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
	while (1)
	{
		// mlx_clear_window(props->mlx, props->window);
		mlx_destroy_image(props->mlx, props->image);
		props->image = mlx_new_image(props->mlx, props->width, props->height);
		rot_x += 1;
		rot_y += 1;
		rot_z += 1;
		plot_vectors(props, 0, rot_y, 0);
		connect_points(props);
		mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
	}
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_map		color_map;
	// t_rgb_map	rgb_map;
	int		fd;
	t_props	props;
	t_line	line;

	// if (argc != 2)
	// {
	// 	ft_printf("Please provide a map!\n");
	// 	return (1);
	// }
	read_map(argv[1], &map);
	read_map(argv[1], &color_map);
	// read_map(argv[1], &rgb_map);
	props.points = ft_calloc((map.rows * map.cols) + 1, sizeof(t_vec2));
	init_matrix(argv[1], &map, 0);
	init_matrix(argv[1], &color_map, 1);
	// init_matrix(argv[1], &rgb_map, 2);
	props.map = map;
	props.color_map = color_map;
	// props.rgb_map = rgb_map;
	props.scale = ft_atoi(argv[2]) / 100.0;

	init_window(&props);
	handle_events(&props);
	
	if (argc == 3)
		spin(&props);
	else
	props.pixel.color = 0x333333;
	// props.pixel.color = 0x555555;
	draw_background(&props);
	// plot_vectors(&props, 0, 0, 0);
	plot_vectors(&props, ft_atoi(argv[3]), ft_atoi(argv[4]), ft_atoi(argv[5]));
	// print_points(&props);
	connect_points(&props);
	
	
	
	mlx_loop(props.mlx);
	for (int i = 0; i < map.rows * map.cols; i++) {
    	free(props.points[i]);
	}
	free(props.points);
return (0);
}
