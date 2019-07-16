#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viccarau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:02:40 by viccarau          #+#    #+#              #
#    Updated: 2019/01/14 07:14:24 by cvictor          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = @gcc
NAME= libft.a
CFLAGS= -Wall -Wextra -Werror -Iincludes
SRC=	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c			\
	ft_isdigit.c ft_isprint.c ft_iswhitespace.c ft_itoa.c ft_lstadd.c		\
	ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c			\
	ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c			\
	ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c		\
	ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c		\
	ft_putstr_fd.c ft_puttab.c ft_skipspaces.c ft_strcat.c ft_strchr.c		\
	ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c	\
	ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c		\
	ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c			\
	ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c 		\
	ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c			\
	ft_toupper.c ft_lst_to_str.c ft_lst_to_strn.c ft_realloc.c 				\
	ft_print_memory.c ft_put_addr.c ft_atoi_base.c ft_strtol.c ft_strtoll.c	\
	ft_lstadd_end.c ft_mem.c get_next_line.c

OBJ=$(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ) : $(SRC)

.PHONY : clean
clean: 	
	@rm -f $(OBJ)

.PHONY : fclean
fclean: clean 	
	@rm -f $(NAME)

.PHONY : re
re: fclean all
