# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 12:55:04 by viccarau          #+#    #+#              #
#    Updated: 2019/10/08 16:17:56 by jaelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SDL2 = ./SDL2.framework
CC = gcc
SRC_DIR = ./srcs/

INC = includes/wolf3d.h includes/draw.h includes/minimap.h

SRC = bmp_reader.c checks.c draw_sprite.c draw_wall.c entity_update.c hud.c \
hud1.c init_entity_update.c init_wolf.c input.c input1.c main.c math.c \
matrix_op.c matrix_op1.c minimap.c minimap1.c parse_map.c parsing.c \
perp_distance.c raycaster.c renderer.c sort_entity_order.c sound.c

OBJ = $(SRC:%.c=$(SRC_DIR)%.o)

LIB_INC = -Iincludes

FLAGS += -Llibft -lft -lm -framework SDL2
CFLAGS += -O2 -O3 $(LIB_INC) -F. -Wall -Wextra -Werror

all: $(NAME)

$(NAME):	$(SDL2) $(OBJ) $(INC)
	make -C libft
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(FLAGS)

$(SDL2):
	@if [ ! -d ./SDL2.framework ]; \
	then curl https://www.libsdl.org/release/SDL2-2.0.10.dmg \
	-o SDL2-2.0.10.dmg ; hdiutil attach SDL2-2.0.10.dmg ; \
	cp -r /Volumes/SDL2/SDL2.framework . ; \
	hdiutil detach /Volumes/SDL2 ; fi; \

$(OBJ): $(INC)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean:	clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
