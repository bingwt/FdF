/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:56 by btan              #+#    #+#             */
/*   Updated: 2024/01/10 13:04:40 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	handle_close(t_props *props)
{
	int	i;
	
	mlx_destroy_image(props->mlx, props->image);
	mlx_destroy_window(props->mlx, props->window);

	i = 0;
	while (i < props->map.rows)
	{
		free(props->map.matrix[i]);
		i++;
	}
	exit(0);
}

static int	handle_keydown(int key, t_props *props)
{
	char	*image;
	t_line	line;

	printf("%d\n", key);
	if (key == 65307)
		handle_close(props);
	if (key == 104)
	{
		props->help = !props->help;
		if (props->help)
		{
			line.y0 = 0;
			line.y1 = props->height - 1;
			line.y0 = 0;
			while (line.x0++ < 170)
			{
				line.x1 = line.x0;
				render_line("aa", &line, props);
			}
			mlx_string_put(props->mlx, props->window, \
			props->width * 0.05, props->height / 2, 0xffffff, "Controls:");
			mlx_string_put(props->mlx, props->window, \
			props->width * 0.05, \
			props->height / 2 + 14, 0xffffff, "Toggle help: h");
			mlx_string_put(props->mlx, props->window, \
			props->width * 0.05, \
			props->height / 2 + 28, 0xffffff, "Quit: ESC");
		}
		else
			mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
		//{
		//	mlx_string_put(props->mlx, props->window, \
		//	props->width * 0.05, \
		//	props->height / 2, 0x000000, "Controls:");
		//	mlx_string_put(props->mlx, props->window, \
		//	props->width * 0.05, \
		//	props->height / 2 + 14, 0x000000, "Toggle help: h");
		//	mlx_string_put(props->mlx, props->window, \
		//	props->width * 0.05, \
		//	props->height / 2 + 28, 0x000000, "Quit: ESC");
		//}
	}
	if (key == 100)
	{
		printf("Test");
		//image = mlx_get_data_addr(props->image, int *bits_per_pixel, int *size_line, int *endian );
		//mlx_string_put(props->mlx, props->image, props->width * 0.05, props->height / 2 + 14, 0xffffff, "Toggle help: h");
		//mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
	}
	if (key == 65361 || key == 65362 || key == 65363 || key ==65364)
	{
		if (key == 65361)
			props->pixel.x--;
		if (key == 65362)
			props->pixel.y--;
		if (key == 65363)
			props->pixel.x++;
		if (key == 65364)
			props->pixel.y++;
		mlx_destroy_image(props->mlx, props->image);
		props->image = mlx_new_image(props->mlx, props->width, props->height);
		draw_pixel(props->pixel.x, props->pixel.y, props);
		draw_pixel(props->pixel.x + 5, props->pixel.y + 5, props);
		mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
	}
	return (0);
}

static int	handle_mouse(int x, int y, void *params)
{
	ft_printf("x: %d, ", x);
	ft_printf("y: %d\n", y);
	return (0);
}

int	handle_events(t_props *props)
{
	mlx_hook(props->window, 2, 1L << 0, handle_keydown, props);
	mlx_hook(props->window, 6, 1L << 6, handle_mouse, &props);
	mlx_hook(props->window, 17, 0L, handle_close, props);
}
