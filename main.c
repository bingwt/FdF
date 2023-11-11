/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2023/11/11 18:05:28 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int	main()
{
	void	*mlx_ptr;
	void	*window;

	mlx_ptr = mlx_init();
	window = mlx_new_window(mlx_ptr, 1024, 1024, "Test");
	mlx_loop(mlx_ptr);
}
