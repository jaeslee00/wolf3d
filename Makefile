#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viccarau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 12:55:04 by viccarau          #+#    #+#              #
#    Updated: 2019/07/16 23:19:57 by viccarau         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d
SRC_DIR = /Users/viccarau/Work/wolf3d/srcs/
INC = includes/camera.h includes/wolf3d.h includes/draw.h
SRC = $(SRC_DIR)checks.c $(SRC_DIR)main.c $(SRC_DIR)keycode.c $(SRC_DIR)math.c \
		$(SRC_DIR)parsing.c
OBJ = $(SRC:$(SRC_DIR)%.c=%.o)

#linux
#LIB=minilibx
LIB_INC=-Iincludes -Ilibft/includes -I ~/Library/Frameworks/SDL2.framework/Headers
#-I$(LIB)
FLAGS += -lm -Llibft -lft -lm -framework SDL2
# -lmlx -L $(LIB)

CFLAGS += -Wall -Wextra -Werror $(LIB_INC) -F.

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