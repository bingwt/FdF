/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:09:20 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 06:35:55 by btan             ###   ########.fr       */
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
		row[i++] = ft_atoi(z[i]);
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
	{
		if (ft_strchr(split[i], ','))
			colors[i++] = ft_atoi_base(ft_strchr(split[i], ',') + 3, base);
		else
			colors[i++] = 0xFFFFFF;
	}
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
