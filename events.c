/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:56 by btan              #+#    #+#             */
/*   Updated: 2024/01/03 20:01:23 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keydown(int key, t_props *props)
{
	char	*image;
	printf("%d\n", key);
	if (key == 65307)
		//mlx_destroy_window((*props).mlx, (*props).window);
		handle_close(key, props);
	if (key == 104)
	{
		(*props).help = !(*props).help;
		if ((*props).help)
		{
			//mlx_string_put((*props).mlx, (*props).window, (*props).width * 0.05, (*props).height / 2, 0xffffff, help);
			mlx_string_put((*props).mlx, (*props).window, (*props).width * 0.05, (*props).height / 2, 0xffffff, "Controls:");
			mlx_string_put((*props).mlx, (*props).window, (*props).width * 0.05, (*props).height / 2 + 14, 0xffffff, "Toggle help: h");
			mlx_string_put((*props).mlx, (*props).window, (*props).width * 0.05, (*props).height / 2 + 28, 0xffffff, "Quit: ESC");
		}
		else
		{
			//mlx_string_put((*props).mlx, (*props).window, (*props).width * 0.05, (*props).height / 2, 0x000000, help);
			mlx_string_put((*props).mlx, (*props).window, (*props).width * 0.05, (*props).height / 2, 0x000000, "Controls:");
			mlx_string_put((*props).mlx, (*props).window, (*props).width * 0.05, (*props).height / 2 + 14, 0x000000, "Toggle help: h");
			mlx_string_put((*props).mlx, (*props).window, (*props).width * 0.05, (*props).height / 2 + 28, 0x000000, "Quit: ESC");
		}
	}
	if (key == 100)
	{
		printf("Test");
		//image = mlx_get_data_addr((*props).image, int *bits_per_pixel, int *size_line, int *endian );
		//mlx_string_put((*props).mlx, (*props).image, (*props).width * 0.05, (*props).height / 2 + 14, 0xffffff, "Toggle help: h");
		//mlx_put_image_to_window((*props).mlx, (*props).window, (*props).image, 0, 0);
	}
	if (key == 65361)
		draw_pixel(pixel, props, props.img);

		mlx_put_image_to_window(props.mlx, props.window, props.image, 0, 0);
	return (0);
}
//
//int	handle_mouse(int x, int y, void *mlx_ptr, void *window)
//{
//	printf("x: %d\ny: %d\n", x, y);
//	//if (key == 65307)
//	//	return (mlx_destroy_window(mlx_ptr, window));
//	return (0);
//}
//
int	handle_close(int key, t_props *props)
{
	free((*props).mlx);
	free((*props).window);
	free((*props).image);
	//free(*props);
	exit(0);
}

int	handle_events(t_props *props)
{
	mlx_hook((*props).window, 2, 1L << 0, handle_keydown, props);
	//mlx_hook(window.ptr, 4, 1L << 2, handle_button, mlx_ptr);
	//mlx_hook((*props).window, 6, 1L << 6, handle_mouse, &props);
	mlx_hook((*props).window, 17, 0L, handle_close, props);
}
