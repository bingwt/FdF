/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:09:20 by btan              #+#    #+#             */
/*   Updated: 2024/01/09 22:46:07 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	read_map(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	(*map).rows = 0;
	map->cols = 0;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
//		ft_printf("%s\n", line);
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

static int	*init_row(char *file, t_map *map)
{
    int		fd;
    int		*row;
    char	*line;
    char	**split;
    int		i;

    fd = open(file, O_RDONLY);
    i = 0;
    row = ft_calloc(map->cols, sizeof(int));
    line = get_next_line(fd);
    split = ft_split(line, ' ');
    while (i < map->cols)
        row[i] = ft_atoi(split[i++]);
    free_strs(split);
    free(line);
    close(fd);
    return (row);
}

void	init_matrix(char *file, t_map *map)
{
	int		i;

	i = 0;
	map->matrix = ft_calloc(map->rows, sizeof(int *));
	while (i < map->rows)
		map->matrix[i++] = init_row(file, map);
}
