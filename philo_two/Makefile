# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: racohen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 23:55:41 by racohen           #+#    #+#              #
#    Updated: 2019/11/25 09:19:23 by racohen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

SAN = -fsanitize=address

NAME = philo_two

LIB_PRINTF = ftprintf

LIB_PATH = srcs/ft_printf/

LIB_COMPIL = -L$(LIB_PATH) -l$(LIB_PRINTF)

SRCS_DIR = srcs/

INCS_DIR = includes/

SRCS_LIST = main.c\
			ft_atol.c\
			phil_utils.c\

SRCS =  $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJECT = $(patsubst %.c, %.o, $(SRCS))

HEADERS = $(INCS_DIR)ft_philo_two.h

all : $(NAME)

.c.o : 
	${CC} -c -I $(INCS_DIR) $< -o ${<:.c=.o}

$(NAME): $(OBJECT) $(INCS_DIR)
	$(CC) $(FLAGS) $(LIB_COMPIL) $(OBJECT) -o $(NAME)

clean:
	@rm -rf $(OBJECT)

fclean: clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: re clean fclean 
