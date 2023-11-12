/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2023/11/12 16:41:37 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>

typedef struct window_size {
	void	*ptr;
	int	width;
	int	height;
}	t_window;

int	handle_keydown(int key, void *mlx_ptr, void *window)
{
	//printf("%d\n", key);
	if (key == 65307)
		return (mlx_destroy_window(mlx_ptr, window));
	return (0);
}

int	handle_mouse(int key, void *mlx_ptr, void *window)
{
	printf("%d\n", key);
	//if (key == 65307)
	//	return (mlx_destroy_window(mlx_ptr, window));
	return (0);
}

int	main(void)
{
	void	*mlx_ptr;
	t_window	window;

	mlx_ptr = mlx_init();
	window.width = 1024;
	window.height = 512;
	window.ptr = mlx_new_window(mlx_ptr, window.width, window.height, "FDF");
	mlx_hook(window.ptr, 2, 1L << 0, handle_keydown, mlx_ptr);
	mlx_hook(window.ptr, 6, 1L << 6, handle_mouse, mlx_ptr);
	mlx_loop(mlx_ptr);
}
