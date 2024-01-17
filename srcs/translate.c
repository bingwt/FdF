/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:49:58 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 23:27:16 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(float ***projection, t_vec2 *translation)
{
	(*projection)[0][0] += translation->x;
	(*projection)[1][0] += translation->y;
}

void	handle_zoom(t_props *props, int key)
{
	if (key == 65362)
		props->scale += 0.01;
	if (key == 65364)
		props->scale -= 0.01;
	mlx_destroy_image(props->mlx, props->image);
	props->image = mlx_new_image(props->mlx, props->width, props->height);
	plot_vectors(props);
	connect_points(props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

void	handle_translation(t_props *props, int key)
{
	if (key == 119)
		props->translation->y -= 1;
	if (key == 115)
		props->translation->y += 1;
	if (key == 97)
		props->translation->x -= 1;
	if (key == 100)
		props->translation->x += 1;
	mlx_destroy_image(props->mlx, props->image);
	props->image = mlx_new_image(props->mlx, props->width, props->height);
	plot_vectors(props);
	connect_points(props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}
