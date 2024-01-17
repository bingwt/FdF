/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:56 by btan              #+#    #+#             */
/*   Updated: 2024/01/17 10:53:52 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	handle_close(t_props *props)
{
	int	i;

	mlx_destroy_image(props->mlx, props->image);
	mlx_destroy_window(props->mlx, props->window);
	mlx_destroy_display(props->mlx);
	free(props->mlx);
	i = 0;
	while (i < props->map.rows)
	{
		free(props->map.matrix[i]);
		free(props->color_map.matrix[i]);
		i++;
	}
	free(props->map.matrix);
	free(props->color_map.matrix);
	free(props->points);
	free(props->rotation);
	free(props->translation);
	exit(0);
}

void	handle_help(t_props *props)
{
	mlx_string_put(props->mlx, props->window, \
		props->width * 0.05, props->height / 2, 0xffffff, "Controls:");
	mlx_string_put(props->mlx, props->window, \
		props->width * 0.05, \
		props->height / 2 + 14, 0xffffff, "Toggle help: h");
	mlx_string_put(props->mlx, props->window, \
		props->width * 0.05, \
		props->height / 2 + 28, 0xffffff, "Quit: ESC");
}

void	handle_rotation(t_props *props, int key)
{
	props->axis_iter = 1;
	if (key == 113)
		props->rotation->z += props->axis_iter;
	if (key == 101)
		props->rotation->z -= props->axis_iter;
	if (key == 44)
		props->rotation->x += props->axis_iter;
	if (key == 46)
		props->rotation->x -= props->axis_iter;
	if (key == 91)
		props->rotation->y += props->axis_iter;
	if (key == 93)
		props->rotation->y -= props->axis_iter;
	mlx_destroy_image(props->mlx, props->image);
	props->image = mlx_new_image(props->mlx, props->width, props->height);
	plot_vectors(props);
	connect_points(props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

static int	handle_keydown(int key, t_props *props)

{
	printf("%d\n", key);
	if (key == 65307)
		handle_close(props);
	if (key == 113 || key == 101 || key == 44 || key == 46 || \
	key == 91 || key == 93)
		handle_rotation(props, key);
	if (key == 65362 || key == 65364)
		handle_zoom(props, key);
	if (key == 119 || key == 115 || key == 97 || key == 100)
		handle_translation(props, key);
	if (key == 104)
	{
		props->help = !props->help;
		if (props->help)
			handle_help(props);
		else
			mlx_put_image_to_window(props->mlx, \
			props->window, props->image, 0, 0);
	}
	return (0);
}

void	handle_events(t_props *props)
{
	mlx_hook(props->window, 2, 1L << 0, handle_keydown, props);
	mlx_hook(props->window, 17, 0L, handle_close, props);
}
