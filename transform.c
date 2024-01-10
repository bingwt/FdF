/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 05:01:00 by btan              #+#    #+#             */
/*   Updated: 2024/01/11 05:06:20 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	rotate_z(float ***matrix, float degrees)
{
	double	angle;
	float	**rotation;
	float	**result;

	angle = degrees * 3.14 / 180;
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
	free(*matrix);
	*matrix = result;
}

void	rotate_x(float ***matrix, float degrees)
{
	double	angle;
	float	**rotation;
	float	**result;

	angle = degrees * 3.14 / 180;
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
	free(*matrix);
	*matrix = result;
}

void	rotate_y(float ***matrix, float degrees)
{
	double	angle;
	float	**rotation;
	float	**result;

	angle = degrees * 3.14 / 180;
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
	free(*matrix);
	*matrix = result;
}