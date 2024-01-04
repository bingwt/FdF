/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:43 by btan              #+#    #+#             */
/*   Updated: 2024/01/04 23:39:45 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;
	t_props	props;
	t_line	line;

	if (argc != 2)
	{
		ft_printf("Please provide a map!\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	read_map(fd, &map);

	props.mlx = mlx_init();
	props.width = WIDTH;
	props.height = HEIGHT;
	props.window = mlx_new_window(props.mlx, props.width, props.height, "FdF");
	props.image = mlx_new_image(props.mlx, props.width, props.height);
	props.background = mlx_new_image(props.mlx, props.width, props.height);
	props.help = 0;

	props.pixel.x = props.width / 2;
	props.pixel.y = props.height / 2;
	props.pixel.color = 0xFFFFFFFF;
	
	line.x0 = 0;
	line.y0 = 0;
	line.x1 = props.width - 1;
	line.y1 = props.height - 1;
	render_line("aa", line, props);
	line.x0 = 0;
	line.y0 = props.height - 1;
	line.x1 = props.width - 1;
	line.y1 = 0;
	render_line("aa", line, props);
	//line.x0 = 0;
	//line.x1 = props.width - 1;
	//line.y0 = 339;
	//while (++line.y0 < 378)
	//{
	//	line.y1 = line.y0;
	//	render_line("aa", line, props);
	//}
	
	handle_events(&props);
	mlx_loop(props.mlx);
}
