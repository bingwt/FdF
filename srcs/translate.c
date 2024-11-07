/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:49:58 by btan              #+#    #+#             */
/*   Updated: 2024/11/08 05:22:11 by btan             ###   ########.fr       */
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
	props->pixel.color = 0x000000;
	draw_background(props);
	if (key == 65362)
		props->scale += 0.01;
	if (key == 65364)
		props->scale -= 0.01;
}

void	handle_translation(t_props *props, int key)
{
	props->pixel.color = 0x000000;
	draw_background(props);
	if (key == 119)
		props->translation->y -= 1;
	if (key == 115)
		props->translation->y += 1;
	if (key == 97)
		props->translation->x -= 1;
	if (key == 100)
		props->translation->x += 1;
}
