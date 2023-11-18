/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2023/11/18 14:25:16 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	t_props	props;

	props.mlx = mlx_init();
	props.width = 1024;
	props.height = 512;
	props.window = mlx_new_window(props.mlx, props.width, props.height, "FDF");
	props.image = mlx_new_image(props.mlx, props.width, props.height);
	props.help = 0;
	//mlx_hook(props.window, 2, 1L << 0, handle_keydown, &props);
//	mlx_hook(window.ptr, 4, 1L << 2, handle_button, mlx_ptr);
	//mlx_hook(props.window, 6, 1L << 6, handle_mouse, props.mlx);
	//mlx_hook(props.window, 17, 0L, handle_close, &props);
	handle_events(&props);
	mlx_loop(props.mlx);
}
