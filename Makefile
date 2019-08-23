# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 12:55:04 by viccarau          #+#    #+#              #
#    Updated: 2019/08/23 01:24:37 by jaelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SDL2 = ~/Library/Frameworks/SDL2.framework
SRC_DIR = ./srcs/
INC = includes/camera.h includes/wolf3d.h includes/draw.h
SRC = $(SRC_DIR)checks.c $(SRC_DIR)main.c $(SRC_DIR)keycode.c $(SRC_DIR)math.c \
	$(SRC_DIR)parsing.c $(SRC_DIR)raycaster.c $(SRC_DIR)debug.c $(SRC_DIR)movement.c
OBJ = $(SRC:$(SRC_DIR)%.c=%.o)

LIB_INC=-Iincludes -Ilibft/includes -I ~/Work/wolf3d/SDL2.framework/Headers
#-I$(LIB)
FLAGS += -Llibft -lft -lm -framework SDL2

CFLAGS += -Wall -Wextra -Werror -g $(LIB_INC) -F.

all: $(NAME)

$(NAME):	$(OBJ) $(SDL2)
	make -C libft
	gcc -o $(NAME) $(OBJ) $(FLAGS) $(CFLAGS)

$(SDL2):
	@if [ ! -d  ~/Library/Frameworks ];then mkdir ~/Library/Frameworks; \
	if [ ! -d ~/Library/Frameworks/SDL2.framework ]; \
	then cp -r SDL2.framework ~/Library/Frameworks/. ; fi; \
	elif [ ! -d ~/Library/Frameworks/SDL2.framework ] \
	;then cp -r SDL2.framework ~/Library/Frameworks/. ; fi



$(OBJ): $(SRC) $(INC)
	gcc -c $(SRC) $(CFLAGS)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean:	clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
