/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 05:00:54 by btan              #+#    #+#             */
/*   Updated: 2024/01/10 14:22:51 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	render_pixel(int x, int y, t_props *props)
{
	draw_pixel(x, y, props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

void	render_line(char *algo, t_line *line, t_props *props)
{
	if (!ft_strncmp(algo, "bresenham", 9) || !ft_strncmp(algo, "a", 2))
		draw_bresenham(line, props);
	if (!ft_strncmp(algo, "xiaolin_wu", 10) || !ft_strncmp(algo, "aa", 2))
		draw_xiaolin_wu(line, props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}
