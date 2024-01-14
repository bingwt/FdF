/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:09:20 by btan              #+#    #+#             */
/*   Updated: 2024/01/14 01:52:28 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	read_map(char *file, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	(*map).rows = 0;
	map->cols = 0;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map->cols)
			map->cols += count_words(line, ' ');
		free(line);
		line = get_next_line(fd);
		(*map).rows++;
	}
	close(fd);
	ft_printf("Rows: %d\n", (*map).rows);
	ft_printf("Columns: %d\n", map->cols);
}

static int	*init_row(char *line, t_map *map)
{
	int		*row;
	char	**z;
	int		i;

	row = ft_calloc(map->cols + 1, sizeof(int));
	z = ft_split(line, ' ');
	i = 0;
	while (i < map->cols)
		row[i] = ft_atoi(z[i++]);
	free_strs(z);
	return (row);
}

static int	*init_colors(char *line, t_map *map)
{
	int		*colors;
	char	**split;
	int		i;
	char	*base;

	colors = ft_calloc(map->cols + 1, sizeof(int));
	split = ft_split(line, ' ');
	i = 0;
	base = "0123456789abcdef";
	while (i < map->cols)
		if (ft_strchr(split[i], ','))
			colors[i++] = ft_atoi_base(ft_strchr(split[i], ',') + 3, base);
		else
			colors[i++] = 0xFFFFFF;
	free_strs(split);
	return (colors);
}

void	init_matrix(char *file, t_map *map, int color)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	map->matrix = ft_calloc(map->rows, sizeof(int *));
	while (i < map->rows)
	{
		if (color)
			map->matrix[i] = init_colors(line, map);
		else
			map->matrix[i] = init_row(line, map);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

// static int	*init_row(char *line, t_map *map, t_vec3 *vec)
// {
// 	int		*row;
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	row = ft_calloc(map->cols + 1, sizeof(int));
// 	split = ft_split(line, ' ');
// 	while (i < map->cols)
// 	{
// 		vec->x = i;
// 		vec->z = ft_atoi(split[i++]);
// 		row[i] = vec->z;
// 	}
// 	free_strs(split);
// 	return (row);
// }

// void	init_matrix(char *file, t_map *map, t_vec3 **points)
// {
// 	int		fd;
// 	int		i;
// 	char	*line;
// 	t_vec3	vec;

// 	fd = open(file, O_RDONLY);
// 	i = 0;
// 	line = get_next_line(fd);
// 	map->matrix = ft_calloc(map->rows, sizeof(int *));
// 	while (i < map->rows)
// 	{
// 		vec.y = i;
// 		map->matrix[i] = init_row(line, map, &vec);
// 		free(line);
// 		line = get_next_line(fd);
// 		*(points)[i] = vec;
// 		i++;
// 	}
// }