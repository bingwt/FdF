/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:09:20 by btan              #+#    #+#             */
/*   Updated: 2024/01/06 15:42:59 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	read_map(int fd, t_map *map)
{
	char	*line;

	(*map).rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
		(*map).rows++;
	}
	ft_printf("Rows: %d\n", (*map).rows);
	ft_printf("Columns: %d\n");
}

void	init_matrix(int fd)
{
	
