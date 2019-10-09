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
SD = ./srcs/

INC = includes/wolf3d.h includes/draw.h includes/minimap.h
SRC = $(SD)main.c $(SD)parsing.c $(SD)raycaster.c $(SD)checks.c $(SD)math.c \
	$(SD)perp_distance.c $(SD)minimap.c $(SD)minimap1.c $(SD)draw_wall.c \
	$(SD)input.c $(SD)input1.c $(SD)bmp_reader.c $(SD)draw_sprite.c $(SD)hud.c \
	$(SD)hud1.c $(SD)init_entity_update.c $(SD)entity_update.c \
	$(SD)sort_entity_order.c $(SD)sound.c $(SD)init_wolf.c $(SD)renderer.c \
	$(SD)matrix_op.c $(SD)matrix_op1.c $(SD)parse_map.c
OBJ = $(SRC:$(SD)%.c=$(SD)%.o)

LIB_INC = -Iincludes

FLAGS += -Llibft -lft -lm -framework SDL2
CFLAGS += -g -O2 -O3 $(LIB_INC) -F. -Wall -Wextra -Werror

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
	rm -rf $(SDL2)
	make -C libft fclean

re: fclean all
