/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2023/11/11 22:09:34 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>

typedef struct window_size {
	void	*ptr;
	int	width;
	int	height;
}	t_window;

int	close(int key, void *mlx_ptr, void *window)
{
	printf("%d\n", key);
	if (key == 65307)
		mlx_destroy_window(mlx_ptr, window);
	return (1);
}

int	main(void)
{
	void	*mlx_ptr;
	t_window	window;

	mlx_ptr = mlx_init();
	window.width = 1024;
	window.height = 512;
	window.ptr = mlx_new_window(mlx_ptr, window.width, window.height, "FDF");
	mlx_hook(window.ptr, 2, 1L << 0, close, mlx_ptr);
	mlx_loop(mlx_ptr);
}
