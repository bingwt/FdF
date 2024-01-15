/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 23:11:57 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 05:08:52 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	**vec3_to_matrix(t_vec3 *vec)
{
	float	**matrix;

	matrix = (float **)malloc(sizeof(float *) * 3);
	matrix[0] = (float *)malloc(sizeof(float) * 1);
	matrix[1] = (float *)malloc(sizeof(float) * 1);
	matrix[2] = (float *)malloc(sizeof(float) * 1);
	matrix[0][0] = vec->x;
	matrix[1][0] = vec->y;
	matrix[2][0] = vec->z;
	return (matrix);
}

t_vec3	*matrix_to_vec3(float **matrix)
{
	t_vec3	*vec;

	vec = (t_vec3 *)malloc(sizeof(t_vec3));
	vec->x = matrix[0][0];
	vec->y = matrix[1][0];
	vec->z = matrix[2][0];
	return (vec);
}

t_vec2	*matrix_to_vec2(float **matrix)
{
	t_vec2	*vec;

	vec = (t_vec2 *)malloc(sizeof(t_vec2));
	vec->x = matrix[0][0];
	vec->y = matrix[1][0];
	return (vec);
}

float	**matrix_mult(float **a, float **b)
{
	float	**matrix;
	int		i;
	int		j;
	int		k;

	matrix = (float **)malloc(sizeof(float *) * 3);
	matrix[0] = (float *)malloc(sizeof(float) * 1);
	matrix[1] = (float *)malloc(sizeof(float) * 1);
	matrix[2] = (float *)malloc(sizeof(float) * 1);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 1)
		{
			matrix[i][j] = 0;
			k = 0;
			while (k < 3)
				matrix[i][j] += a[i][k] * b[k++][j];
			j++;
		}
		i++;
	}
	return (matrix);
}

void	free_matrix(float **matrix)
{
	int	i;

	i = 0;
	while (i < 3)
		free(matrix[i++]);
	free(matrix);
}

// int main() {
//     t_vec3 vec3;
//     float **transformation;
//     float **matrix;

// 	transformation = (float **)malloc(sizeof(float *) * 2);
// 	transformation[0] = (float *)malloc(sizeof(float) * 3);
// 	transformation[1] = (float *)malloc(sizeof(float) * 3);
// 	transformation[0][0] = 1;
// 	transformation[0][1] = 0;
// 	transformation[0][2] = 0;
// 	transformation[1][0] = 0;
// 	transformation[1][1] = 1;
// 	transformation[1][2] = 0;
//     vec3.x = 1;
//     vec3.y = 1;
//     vec3.z = 1;
//     matrix = vec3_to_matrix(&vec3);
//     // show_matrix(matrix);
//     matrix = matrix_mult(transformation, matrix);
//     show_matrix(matrix);
// }