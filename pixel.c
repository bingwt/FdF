/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 00:54:47 by btan              #+#    #+#             */
/*   Updated: 2024/01/14 23:56:50 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

// void	draw_pixel(int x, int y, t_props props)
// {
// 	char	*buffer;
// 	int		pixel;
// 	int		pixel_bits;
// 	int		line_bytes;

// 	buffer = mlx_get_data_addr(props->image, &pixel_bits, &line_bytes, &props->img.endian);
// 	props->pixel.color = mlx_get_color_value(props->mlx, props->pixel.color);
// 	pixel = (y * line_bytes) + (x * 4);
// 	if (props->img.endian == 1)
// 	{
// 		buffer[pixel + 0] = (props->pixel.color >> 24);
// 		buffer[pixel + 1] = (props->pixel.color >> 16) & 0xFF;
// 		buffer[pixel + 2] = (props->pixel.color >> 8) & 0xFF;
// 		buffer[pixel + 3] = (props->pixel.color) & 0xFF;
// 	}

// 	else if (props->img.endian == 0)
// 	{
// 		buffer[pixel + 0] = (props->pixel.color) & 0xFF;
// 		buffer[pixel + 1] = (props->pixel.color >> 8) & 0xFF;
// 		buffer[pixel + 2] = (props->pixel.color >> 16) & 0xFF;
// 		buffer[pixel + 3] = (props->pixel.color >> 24);
// 	}
// }

void	draw_pixel(int x, int y, t_props *props)
{
	char	*buffer;
	int		offset;
	int		pixel_bits;
	int		line_bytes;

	pixel_bits = props->img.pixel_bits;
	line_bytes = props->img.line_bytes;
	buffer = mlx_get_data_addr(props->image, &pixel_bits, &line_bytes, &props->img.endian);
	offset = (line_bytes * y) + (x * (pixel_bits / 8));	
	*((unsigned int *)(offset + buffer)) = props->pixel.color;
	//*((unsigned int *)(offset + buffer)) = (props->pixel.alpha << 24) | props->pixel.color;
}

t_color    *hex_to_rgb(char *hex)
{
    char    *base;
    t_color *color;

    base = "0123456789abcdef";
    color = calloc(1, sizeof(t_color));
    color->blue = ft_atoi_base(hex + 4, base);
    hex[4] = '\0';
    color->green = ft_atoi_base(hex + 2, base);
    hex[2] = '\0';
    color->red = ft_atoi_base(hex, base);
    return (color);
}

t_color *dec_to_rgb(int dec)
{
    t_color *color;

    color = calloc(1, sizeof(t_color));
    color->blue = dec % 256;
    dec = dec / 256;
    color->green = dec % 256;
    dec = dec / 256;
    color->red = dec % 256;
    return (color);
}

int		rgb_to_dec(t_color *color)
{
    int dec;

    if (!color)
        return (0);
    dec = 0;
    dec =  dec + color->red * 256 * 256;
    dec = dec + color->green * 256;
    dec = dec + color->blue;
    return (dec);
}

t_color *color_lerp(t_color *color1, t_color *color2, float t)
{
    t_color *color;

    color = calloc(1, sizeof(t_color));
    color->red = color1->red + (color2->red - color1->red) * t;
    color->green = color1->green + (color2->green - color1->green) * t;
    color->blue = color1->blue + (color2->blue - color1->blue) * t;
    return (color);
}

t_color *color_step(t_color *color1, t_color *color2, int ppu)
{
    t_color *step;

    if (!color1 || !color2)
        return (0);
    step = calloc(1, sizeof(t_color));
    step->red = (color1->red - color2->red) % (ppu + 1);
    step->green = (color1->green - color2->green) % (ppu + 1);
    step->blue = (color1->blue - color2->blue) % (ppu + 1);
    return (step);
}