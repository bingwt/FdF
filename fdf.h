/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:38 by btan              #+#    #+#             */
/*   Updated: 2023/11/13 23:59:30 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>

typedef struct properties {
	void	*mlx;
	void	*window;
	int	width;
	int	height;
	int	help;
}	t_props;

int	handle_keydown(int key, t_props *props);
int	handle_mouse(int x, int y, void *mlx_ptr, void *window);
int	handle_close(int key, t_props *props);
int	handle_events(t_props *props);
