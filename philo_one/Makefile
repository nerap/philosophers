# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: racohen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 23:55:41 by racohen           #+#    #+#              #
#    Updated: 2020/07/02 09:21:49 by racohen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

SAN = -fsanitize=address

NAME = philo_one

LIB_COMPIL = -pthread

SRCS_DIR = srcs/

INCS_DIR = includes/

SRCS_LIST = main.c\
			ft_atol.c\
			ft_strdup.c\
			ft_strjoinfreeboth.c\
			ft_strlen.c\
			ft_itoa.c\
			phil_utils.c\

SRCS =  $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJECT = $(patsubst %.c, %.o, $(SRCS))

HEADERS = $(INCS_DIR)ft_philo_one.h

all : $(NAME)

.c.o : 
	${CC} -c -I $(INCS_DIR) $< -o ${<:.c=.o}

$(NAME): $(OBJECT) $(INCS_DIR)
	$(CC) $(FLAGS) $(OBJECT) -o $(NAME) $(LIB_COMPIL)

clean:
	@rm -rf $(OBJECT)

fclean: clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: re clean fclean 
