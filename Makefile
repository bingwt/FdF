# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 15:06:39 by btan              #+#    #+#              #
#    Updated: 2024/01/17 13:41:39 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

INCLUDES = includes

SRCS = srcs/main.c \
		srcs/fdf_utils.c \
		srcs/matrix_math.c \
		srcs/normalize.c \
		srcs/transform.c \
		srcs/translate.c \
		srcs/map.c \
		srcs/pixel.c \
		srcs/vectors.c \
		srcs/connect.c \
		srcs/draw.c \
		srcs/events.c

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

MLXFLAGS = -lXext -lX11

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	make -C Libft
	mv ./Libft/libft.a ./
	make fclean -C Libft
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -I$(INCLUDES) -ILibft -Imlx libft.a mlx.a -lm -lXext -lX11

clean:
	rm -rf $(OBJECTS) $(NAME).a libft.a

fclean: clean
	rm -rf $(NAME)

re: fclean all

gnl:
	cc test_gnl.c -ILibft -LLibft -l:libft.a -g
test-make:
	make -C Libft
	mv ./Libft/libft.a ./
	make -C mlx
	mv ./mlx/libmlx_Linux.a ./mlx.a
	make fclean -C Libft
	make clean -C mlx
test: test-make
	cc main.c fdf_utils.c matrix_math.c normalize.c transform.c map.c pixel.c vectors.c connect.c draw.c events.c -I. -Imlx -ILibft libft.a mlx.a -lX11 -lXext -lm -g
	#cc main.c events.c -Imlx -Lmlx -lmlx -ILibft -LLibft -l:libft.a -lXext -lX11 -g
test-720: test-make
	cc main.c fdf_utils.c matrix_math.c normalize.c transform.c map.c pixel.c vectors.c connect.c draw.c events.c -I. -Imlx -ILibft libft.a mlx.a -lX11 -lXext -lm -D WIDTH=1280 -D HEIGHT=720 -g
run:
	clear && ./a.out
tester:
	$(CC) tests/test_fdf.c -L -l $(NAME) -o tester && ./tester && rm tester
.PHONY: all clean fclean re
