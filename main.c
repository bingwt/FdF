/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2024/01/11 06:47:50 by btan             ###   ########.fr       */
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

void	set_scale(float	***matrix, float scale)
{
	(*matrix)[0][0] *= scale;
	(*matrix)[1][0] *= scale;
}

void	set_offset(float	***matrix)
{
	(*matrix)[0][0] += WIDTH / 2;
	(*matrix)[1][0] += HEIGHT / 4;
}

int	pixels_per_unit(t_props *props)
{
	int	pixels;

	if (WIDTH / props->map.cols > HEIGHT / props->map.rows)
		pixels = HEIGHT / props->map.rows;
	else
		pixels = WIDTH / props->map.cols;
}

void	plot_vectors(t_props *props)
{
	int	row;
	int	col;
	t_vec3	*vec3;
	float	**transformation;
	float	**matrix;
	float	**ortho;

	transformation = ft_calloc(3, sizeof(int *));
	transformation[0] = ft_calloc(3, sizeof(int));
	transformation[1] = ft_calloc(3, sizeof(int));
	transformation[2] = ft_calloc(3, sizeof(int));
	transformation[0][0] = 1;
	transformation[0][1] = 0;
	transformation[0][2] = 0;
	transformation[1][0] = 0;
	transformation[1][1] = 1;
	transformation[1][2] = 0;
	transformation[2][0] = 0;
	transformation[2][1] = 0;
	transformation[2][2] = 1;
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
			matrix = vec3_to_matrix(vec3);
			ortho = matrix_mult(transformation, matrix);
			for (int i = 0; i < 3; i++) {
				free(matrix[i]);
			}
			free(matrix);
			if (vec3->z > 1)
				props->pixel.color = 0x00ff00;
			if (vec3->z > 10)
				props->pixel.color = 0x00ffff;
			else
				props->pixel.color = 0xffffff;
			free(vec3);
			// rotate_z(&ortho, degrees);
			// rotate_x(&ortho, degrees);
			rotate_z(&ortho, 45);
			rotate_x(&ortho, 54.7);
			// rotate_y(&ortho, 0);
			set_scale(&ortho, pixels_per_unit(props) * 0.7);
			set_offset(&ortho);
			// set_scale(&ortho, 10);
			props->points[row * props->map.cols + col] = matrix_to_vec2(ortho);
			if (ortho[0][0] >= 0 && ortho[0][0] < props->width && ortho[1][0] >= 0 && ortho[1][0] < props->height)
					draw_pixel(ortho[0][0], ortho[1][0], props);
			for (int i = 0; i < 3; i++) {
				free(ortho[i]);
			}
			free(ortho);
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
				line.x0 = props->points[row * props->map.cols + col]->x;
				line.y0 = props->points[row * props->map.cols + col]->y;
				line.x1 = props->points[row * props->map.cols + col + 1]->x;
				line.y1 = props->points[row * props->map.cols + col + 1]->y;
				draw_bresenham(&line, props);
				// mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);

			}
			if (row + 1 < props->map.rows)
			{
				line.x0 = props->points[row * props->map.cols + col]->x;
				line.y0 = props->points[row * props->map.cols + col]->y;
				line.x1 = props->points[(row + 1) * props->map.cols + col]->x;
				line.y1 = props->points[(row + 1) * props->map.cols + col]->y;
				draw_bresenham(&line, props);
				// mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);

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

	if (argc != 2)
	{
		ft_printf("Please provide a map!\n");
		return (1);
	}
	read_map(argv[1], &map);
	props.points = ft_calloc((map.rows * map.cols) + 1, sizeof(t_vec2));
	init_matrix(argv[1], &map);
	// init_matrix(argv[1], &map, &points);
	// show_matrix(&map);
	props.map = map;

	init_window(&props);
	handle_events(&props);
	
	// int	rotation = 0;

	// while (rotation < 360)
	// {
	// 	plot_vectors(&props, rotation);
	// 	// connect_points(&props);
	// 	mlx_destroy_image(props.mlx, props.image);
	// 	props.image = mlx_new_image(props.mlx, props.width, props.height);
	// 	rotation++;
	// 	ft_printf("rotation: %d\n", rotation);
	// 	if (rotation == 360)
	// 		rotation = 0;
	// }
	// plot_vectors(&props, 10);
	// connect_points(&props);
	plot_vectors(&props);
	// print_points(&props);
	// connect_points(&props);
	
	
	
	mlx_loop(props.mlx);
	for (int i = 0; i < map.rows * map.cols; i++) {
    	free(props.points[i]);
	}
	free(props.points);
return (0);
}
