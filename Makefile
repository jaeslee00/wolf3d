# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 12:55:04 by viccarau          #+#    #+#              #
#    Updated: 2019/09/08 01:20:48 by jaelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SDL2 = ./SDL2.framework
CC = gcc
SRC_DIR = ~/Work/wolf3d/srcs/

INC = includes/wolf3d.h includes/draw.h includes/minimap.h
SRC = $(SRC_DIR)main.c $(SRC_DIR)parsing.c \
	$(SRC_DIR)raycaster.c $(SRC_DIR)checks.c  \
	$(SRC_DIR)math.c $(SRC_DIR)keycode.c $(SRC_DIR)perp_distance.c $(SRC_DIR)minimap.c $(SRC_DIR)minimap1.c \
	$(SRC_DIR)draw_wall.c $(SRC_DIR)input.c $(SRC_DIR)input1.c $(SRC_DIR)bmp_reader.c \
	$(SRC_DIR)draw_sprite.c $(SRC_DIR)hud.c $(SRC_DIR)hud1.c \
	$(SRC_DIR)entity_update.c $(SRC_DIR)sort_entity_order.c $(SRC_DIR)sound.c $(SRC_DIR)init_wolf.c \
	$(SRC_DIR)renderer.c $(SRC_DIR)matrix_op.c $(SRC_DIR)matrix_op1.c $(SRC_DIR)parse_map.c
OBJ = $(SRC:$(SRC_DIR)%.c=$(SRC_DIR)%.o)

LIB_INC = -Iincludes

FLAGS += -Llibft -lft -lm -framework SDL2
CFLAGS += -g $(LIB_INC) -F. -Wall -Wextra -Werror

all: $(NAME)

$(NAME):	$(OBJ) $(INC)
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
#	make -C libft clean

fclean:	clean
	rm -f $(NAME)
#	make -C libft fclean

re: fclean all
