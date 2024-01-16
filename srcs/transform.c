/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 05:01:00 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 23:10:33 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	**orthographic(void)
{
	float	**matrix;

	matrix = ft_calloc(3, sizeof(int *));
	matrix[0] = ft_calloc(3, sizeof(int));
	matrix[1] = ft_calloc(3, sizeof(int));
	matrix[2] = ft_calloc(3, sizeof(int));
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	return (matrix);
}

void	rotate_z(float ***matrix, float degrees)
{
	double	angle;
	float	**rotation;
	float	**result;

	angle = degrees * (M_PI / 180);
	rotation = ft_calloc(3, sizeof(int *));
	rotation[0] = ft_calloc(3, sizeof(int));
	rotation[1] = ft_calloc(3, sizeof(int));
	rotation[2] = ft_calloc(3, sizeof(int));
	rotation[0][0] = cos(angle);
	rotation[0][1] = -sin(angle);
	rotation[0][2] = 0;
	rotation[1][0] = sin(angle);
	rotation[1][1] = cos(angle);
	rotation[1][2] = 0;
	rotation[2][0] = 0;
	rotation[2][1] = 0;
	rotation[2][2] = 1;
	result = matrix_mult(rotation, *matrix);
	free_matrix(rotation);
	free_matrix(*matrix);
	*matrix = result;
}

void	rotate_x(float ***matrix, float degrees)
{
	double	angle;
	float	**rotation;
	float	**result;

	angle = degrees * (M_PI / 180);
	rotation = ft_calloc(3, sizeof(int *));
	rotation[0] = ft_calloc(3, sizeof(int));
	rotation[1] = ft_calloc(3, sizeof(int));
	rotation[2] = ft_calloc(3, sizeof(int));
	rotation[0][0] = 1;
	rotation[0][1] = 0;
	rotation[0][2] = 0;
	rotation[1][0] = 0;
	rotation[1][1] = cos(angle);
	rotation[1][2] = -sin(angle);
	rotation[2][0] = 0;
	rotation[2][1] = sin(angle);
	rotation[2][2] = cos(angle);
	result = matrix_mult(rotation, *matrix);
	free_matrix(rotation);
	free_matrix(*matrix);
	*matrix = result;
}

void	rotate_y(float ***matrix, float degrees)
{
	double	angle;
	float	**rotation;
	float	**result;

	angle = degrees * (M_PI / 180);
	rotation = ft_calloc(3, sizeof(int *));
	rotation[0] = ft_calloc(3, sizeof(int));
	rotation[1] = ft_calloc(3, sizeof(int));
	rotation[2] = ft_calloc(3, sizeof(int));
	rotation[0][0] = cos(angle);
	rotation[0][1] = 0;
	rotation[0][2] = sin(angle);
	rotation[1][0] = 0;
	rotation[1][1] = 1;
	rotation[1][2] = 0;
	rotation[2][0] = -sin(angle);
	rotation[2][1] = 0;
	rotation[2][2] = cos(angle);
	result = matrix_mult(rotation, *matrix);
	free_matrix(rotation);
	free_matrix(*matrix);
	*matrix = result;
}

void	rotate_xyz(float ***projection, t_vec3 *rotation)
{
	rotate_z(projection, rotation->z);
	rotate_x(projection, rotation->x);
	rotate_y(projection, rotation->y);
}
