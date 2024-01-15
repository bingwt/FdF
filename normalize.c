/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 00:41:54 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 05:54:50 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	set_local_origin(t_props *props, t_vec3 **vec3)
{
	int	offset_x;
	int	offset_y;

	offset_x = props->map.cols / 2;
	offset_y = props->map.rows / 2;
	(*vec3)->x -= offset_x;
	(*vec3)->y -= offset_y;
}

void	set_world_origin(t_props *props, float ***matrix)
{
	int	offset_x;
	int	offset_y;

	offset_x = WIDTH / 2;
	offset_y = HEIGHT / 2;
	(*matrix)[0][0] += offset_x;
	(*matrix)[1][0] += offset_y;
}
