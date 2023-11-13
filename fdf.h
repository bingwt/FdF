/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:38 by btan              #+#    #+#             */
/*   Updated: 2023/11/13 19:17:18 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>

typedef struct window_size {
	void	*ptr;
	int	width;
	int	height;
}	t_window;

int	handle_keydown(int key, void *mlx_ptr, void *window);
int	handle_mouse(int x, int y, void *mlx_ptr, void *window);
int	handle_close(int key, void *mlx_ptr, void *window);
