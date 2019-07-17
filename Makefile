#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viccarau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 12:55:04 by viccarau          #+#    #+#              #
#    Updated: 2019/07/16 23:19:57 by marvin           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d
SRC_DIR = ~/Work/wolf3d/srcs/
INC = includes/camera.h includes/fdf.h includes/draw.h
SRC = $(SRC_DIR)camera2.c $(SRC_DIR)camera3.c $(SRC_DIR)camera.c \
	$(SRC_DIR)checks.c $(SRC_DIR)draw2.c $(SRC_DIR)draw3.c $(SRC_DIR)draw.c \
	$(SRC_DIR)wolf3d.c $(SRC_DIR)keycode.c $(SRC_DIR)math.c \
	$(SRC_DIR)matrix_op2.c $(SRC_DIR)matrix_op.c $(SRC_DIR)parsing.c
OBJ = $(SRC:$(SRC_DIR)%.c=%.o)

#linux
#LIB=minilibx
LIB_INC=-Iincludes -Ilibft/includes
#-I$(LIB)
#FLAGS+= $(LIB_INC) -lm -lXext -lX11
# -lmlx -L $(LIB) 

CFLAGS += -g -Wall -Wextra -Werror $(LIB_INC) -Llibft -lft -lm -lSDL2_image -lSDL2

all: $(NAME)

$(NAME):	$(OBJ)
	make -C libft
	gcc -o $(NAME) $(OBJ) $(FLAGS) $(CFLAGS)

$(OBJ): $(SRC) $(INC)
	gcc -c $(SRC) $(CFLAGS)

#	make -C $(LIB)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean:	clean
	rm -f $(NAME)
	make -C libft fclean
#	make -C $(LIB) clean

re: fclean all
