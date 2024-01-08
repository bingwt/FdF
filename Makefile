# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 15:06:39 by btan              #+#    #+#              #
#    Updated: 2024/01/08 12:16:56 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf.a

SRCS = 

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -lmlx -lXext -lX11

OBJECTS = $(SRCS:.c=.o)

all: $(NAME) 

#.c.o:
#	$(CC) -c $< -o $(<:.c=.o)
%.o: %.c
	$(CC) $(CFLAGS) $(MLXFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	make -C Libft
	ar -rc $(NAME) $(OBJECTS)

clean:
	rm -rf $(OBJECTS)

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
	cc main.c fdf_utils.c map.c draw.c render.c events.c -I. -Imlx -ILibft libft.a mlx.a -lX11 -lXext -g
	#cc main.c events.c -Imlx -Lmlx -lmlx -ILibft -LLibft -l:libft.a -lXext -lX11 -g
test-720: test-make
	cc main.c fdf_utils.c map.c draw.c render.c events.c -I. -Imlx -ILibft libft.a mlx.a -lX11 -lXext -D WIDTH=1280 -D HEIGHT=720 -g
run:
	clear && ./a.out
tester:
	$(CC) tests/test_fdf.c -L -l $(NAME) -o tester && ./tester && rm tester
.PHONY: all clean fclean re
