/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2023/11/13 19:37:41 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	void	*mlx_ptr;
	t_window	window;

	mlx_ptr = mlx_init();
	window.width = 1024;
	window.height = 512;
	window.ptr = mlx_new_window(mlx_ptr, window.width, window.height, "FDF");
	mlx_hook(window.ptr, 2, 1L << 0, handle_keydown, mlx_ptr);
//	mlx_hook(window.ptr, 4, 1L << 2, handle_button, mlx_ptr);
	mlx_hook(window.ptr, 6, 1L << 6, handle_mouse, mlx_ptr);
	mlx_hook(window.ptr, 17, 0L, handle_close, mlx_ptr);
//	handle_events(mlx_ptr, &window);
	mlx_loop(mlx_ptr);
}
