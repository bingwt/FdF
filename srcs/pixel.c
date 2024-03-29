/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 00:54:47 by btan              #+#    #+#             */
/*   Updated: 2024/01/16 17:00:05 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(int x, int y, t_props *props)
{
	char	*buffer;
	int		offset;
	int		pixel_bits;
	int		line_bytes;

	pixel_bits = props->img.pixel_bits;
	line_bytes = props->img.line_bytes;
	buffer = mlx_get_data_addr(props->image, &pixel_bits, \
	&line_bytes, &props->img.endian);
	offset = (line_bytes * y) + (x * (pixel_bits / 8));
	if (x >= 0 && x < props->width && y >= 0 && y < props->height)
		*((unsigned int *)(offset + buffer)) = props->pixel.color;
}

t_color	*hex_to_rgb(char *hex)
{
	char	*base;
	t_color	*color;

	base = "0123456789abcdef";
	color = calloc(1, sizeof(t_color));
	color->blue = ft_atoi_base(hex + 4, base);
	hex[4] = '\0';
	color->green = ft_atoi_base(hex + 2, base);
	hex[2] = '\0';
	color->red = ft_atoi_base(hex, base);
	return (color);
}

t_color	*dec_to_rgb(int dec)
{
	t_color	*color;

	color = calloc(1, sizeof(t_color));
	color->blue = dec % 256;
	dec = dec / 256;
	color->green = dec % 256;
	dec = dec / 256;
	color->red = dec % 256;
	return (color);
}

int	rgb_to_dec(t_color *color)
{
	int	dec;

	if (!color)
		return (0);
	dec = 0;
	dec = dec + color->red * 256 * 256;
	dec = dec + color->green * 256;
	dec = dec + color->blue;
	return (dec);
}

t_color	*color_step(int color1, int color2, int ppu)
{
	t_color	*rgb1;
	t_color	*rgb2;
	t_color	*step;

	rgb1 = dec_to_rgb(color1);
	rgb2 = dec_to_rgb(color2);
	step = calloc(1, sizeof(t_color));
	step->red = (rgb1->red - rgb2->red) / ppu;
	step->green = (rgb1->green - rgb2->green) / ppu;
	step->blue = (rgb1->blue - rgb2->blue) / ppu;
	free(rgb1);
	free(rgb2);
	return (step);
}
