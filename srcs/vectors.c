/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 05:32:12 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 07:37:48 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	**ortho_projection(float ***matrix)
{
	float	**transformation;
	float	**projection;

	transformation = orthographic();
	projection = matrix_mult(transformation, *matrix);
	free_matrix(transformation);
	return (projection);
}

static void	process_vector(t_props *props, int row, int col)
{
	t_vec3	*vec3;
	float	**matrix;
	float	**projection;

	vec3 = ft_calloc(1, sizeof(t_vec3));
	vec3->x = col;
	vec3->y = row;
	vec3->z = props->map.matrix[row][col];
	set_local_origin(props, &vec3);
	matrix = vec3_to_matrix(vec3);
	projection = ortho_projection(&matrix);
	free_matrix(matrix);
	free(vec3);
	rotate_xyz(&projection, &props->rotation);
	set_scale(&projection, pixels_per_unit(props) * props->scale);
	set_world_origin(&projection);
	props->points[(row * props->map.cols) + col] = matrix_to_vec2(projection);
	free_matrix(projection);
}

void	plot_vectors(t_props *props)
{
	int		row;
	int		col;

	row = 0;
	while (row < props->map.rows)
	{
		col = 0;
		while (col < props->map.cols)
		{
			process_vector(props, row, col);
			col++;
		}
		row++;
	}
}
