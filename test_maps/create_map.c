/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:50:31 by btan              #+#    #+#             */
/*   Updated: 2024/01/09 13:06:13 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

int	main(int argc, char **argv)
{
	int	rows = atoi(argv[1]);
	int	cols = atoi(argv[2]);

	int	fd = open("new_map.fdf", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	dup2(fd, 1);
	close(fd);
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (col == cols - 1)
				printf("0");
			else
				printf("0 ");
		}
		printf("\n");
	}
}
