/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:56 by btan              #+#    #+#             */
/*   Updated: 2024/01/13 20:06:51 by btan             ###   ########.fr       */
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
			mlx_string_put(props->mlx, props->window, \
			props->width * 0.05, props->height / 2, 0x000700, "Controls:");
			mlx_string_put(props->mlx, props->window, \
			props->width * 0.05, \
			props->height / 2 + 14, 0xff07ff, "Toggle help: h");
			mlx_string_put(props->mlx, props->window, \
			props->width * 0.05, \
			props->height / 2 + 28, 0xff07ff, "Quit: ESC");
		}
		else
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
