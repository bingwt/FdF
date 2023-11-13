/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:56 by btan              #+#    #+#             */
/*   Updated: 2023/11/13 19:35:04 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keydown(int key, void *mlx_ptr, void *window)
{
	//printf("%d\n", key);
	if (key == 65307)
		return (mlx_destroy_window(mlx_ptr, window));
	return (0);
}

int	handle_mouse(int x, int y, void *mlx_ptr, void *window)
{
	printf("x: %d\ny: %d\n", x, y);
	//if (key == 65307)
	//	return (mlx_destroy_window(mlx_ptr, window));
	return (0);
}

int	handle_close(int key, void *mlx_ptr, void *window)
{
	return (mlx_destroy_window(mlx_ptr, window));
}

//int	handle_events(void *mlx_ptr, void *window)
//{
//	mlx_hook(window.ptr, 2, 1L << 0, handle_keydown, mlx_ptr);
//	//mlx_hook(window.ptr, 4, 1L << 2, handle_button, mlx_ptr);
//	mlx_hook(window.ptr, 6, 1L << 6, handle_mouse, mlx_ptr);
//	mlx_hook(window.ptr, 17, 0L, handle_close, mlx_ptr);
//}
