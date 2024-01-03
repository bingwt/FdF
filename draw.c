/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:51:56 by btan              #+#    #+#             */
/*   Updated: 2024/01/03 19:10:45 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

//void	draw_pixel(t_pixel pix, t_props props, t_img img)
//{
//	char	*buffer;
//	int 	pixel;
//	int		bit;
//
//	buffer = mlx_get_data_addr(props.image, &img.pixel_bits, &img.line_bytes, &img.endian);
//	pix.color = mlx_get_color_value(props.mlx, pix.color);
//	pixel = (pix.y * img.line_bytes) + (pix.x * 4);
//	if (img.endian == 1)
//	{
//		buffer[pixel + 0] = (pix.color >> 24);
//		buffer[pixel + 1] = (pix.color >> 16) & 0xFF;
//		buffer[pixel + 2] = (pix.color >> 8) & 0xFF;
//		buffer[pixel + 3] = (pix.color) & 0xFF;
//	}
//
//	else if (img.endian == 0)
//	{
//		buffer[pixel + 0] = (pix.color) & 0xFF;
//		buffer[pixel + 1] = (pix.color >> 8) & 0xFF;
//		buffer[pixel + 2] = (pix.color >> 16) & 0xFF;
//		buffer[pixel + 3] = (pix.color >> 24);
//	}
//}

void	draw_pixel(t_pixel pix, t_props props, t_img img)
{
	char	*buffer;
	int	offset;

	buffer = mlx_get_data_addr(props.image, &img.pixel_bits, &img.line_bytes, &img.endian);
	offset = (img.line_bytes * pix.y) + (pix.x * (img.pixel_bits / 8));	
	*((unsigned int *)(offset + buffer)) = pix.color;
}
