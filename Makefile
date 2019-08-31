# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 12:55:04 by viccarau          #+#    #+#              #
#    Updated: 2019/08/31 05:22:10 by jaelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SDL2 = ./SDL2.framework

SRC_DIR = ./srcs/

INC = includes/camera.h includes/wolf3d.h includes/draw.h
SRC = $(SRC_DIR)checks.c $(SRC_DIR)main.c $(SRC_DIR)keycode.c $(SRC_DIR)math.c \
	$(SRC_DIR)parsing.c $(SRC_DIR)raycaster.c $(SRC_DIR)debug.c \
	$(SRC_DIR)input1.c $(SRC_DIR)minimap.c $(SRC_DIR)perp_distance.c \
	$(SRC_DIR)draw_wall.c $(SRC_DIR)input.c $(SRC_DIR)bmp_reader.c
OBJ = $(SRC:$(SRC_DIR)%.c=%.o)

LIB_INC = -Iincludes -Ilibft/includes -I ./SDL2.framework/Headers
#-I$(LIB)
FLAGS += -Llibft -lft -lm -framework SDL2

CFLAGS += $(LIB_INC) -F. -Wall -Wextra -Werror -fsanitize=address -g

all: $(NAME)

$(NAME):	$(OBJ) $(SDL2)
	make -C libft
	gcc -o $(NAME) $(OBJ) $(FLAGS) $(CFLAGS)

$(SDL2):
	@if [ ! -d ./SDL2.framework ]; \
	then curl https://www.libsdl.org/release/SDL2-2.0.10.dmg \
	-o SDL2-2.0.10.dmg ; hdiutil attach SDL2-2.0.10.dmg ; \
	cp -r /Volumes/SDL2/SDL2.framework . ; \
	hdiutil detach /Volumes/SDL2 ; fi; \

$(OBJ) : $(SRC) $(INC) $(SDL2)
	gcc -c $(SRC) $(CFLAGS)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean:	clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
