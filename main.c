/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2024/01/04 03:08:34 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	t_props	props;

	props.mlx = mlx_init();
	props.width = 1920;
	props.height = 1080;
	props.window = mlx_new_window(props.mlx, props.width, props.height, "FdF");
	props.image = mlx_new_image(props.mlx, props.width, props.height);
	props.background = mlx_new_image(props.mlx, props.width, props.height);
	props.help = 0;

	props.pixel.x = props.width / 2;
	props.pixel.y = props.height / 2;
	props.pixel.color = 0xFFFFFFFF;
	
	
	//draw_pixel(props.pixel.x, props.pixel.y, props);
	//draw_pixel(--props.width, 0, props);
	//fill_pixels(props);
	draw_line(0, 0, props.width - 1, props.height - 1, props);

	mlx_put_image_to_window(props.mlx, props.window, props.image, 0, 0);
	//mlx_destroy_image(props.mlx, props.image);
	//props.image = mlx_new_image(props.mlx, props.width, props.height);
	//draw_pixel(10, 10, pixel, props);
	//mlx_put_image_to_window(props.mlx, props.window, props.image, 0, 0);

	handle_events(&props);
	mlx_loop(props.mlx);
}
