# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: racohen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 17:23:01 by racohen           #+#    #+#              #
#    Updated: 2019/11/25 05:27:41 by racohen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRCS_DIR = srcs/

INCS_DIR = includes/

SRCS = 	ft_printf.c\
		srcs/ft_format_parser.c\
		srcs/write_c.c\
		srcs/write_d.c\
		srcs/write_p.c\
		srcs/write_pp.c\
		srcs/write_s.c\
		srcs/write_u.c\
		srcs/write_pr.c\
		srcs/write_x.c\
		srcs/utils/ft_atoi.c\
		srcs/utils/ft_atoi_size.c\
		srcs/utils/ft_freeall.c\
		srcs/utils/ft_itoa.c\
		srcs/utils/ft_itoa_u.c\
		srcs/utils/ft_memcpy.c\
		srcs/utils/ft_setup_form.c\
		srcs/utils/ft_strdup.c\
		srcs/utils/ft_strjoinfree.c\
		srcs/utils/ft_strjoinfreeboth.c\
		srcs/utils/ft_strlen.c\
		srcs/utils/ft_substr.c\
		srcs/flags/ft_flags.c\
	 
HEADERS = $(INCS_DIR)ft_printf.h

OBJECT = ${SRCS:.c=.o}

all : $(NAME)

.c.o : 
	${CC} ${FLAGS} -c -I $(INCS_DIR) $< -o ${<:.c=.o}

$(NAME): $(OBJECT) $(HEADERS)
	@ar rc $(NAME) $(OBJECT)
	@ranlib $(NAME)

clean:
	@rm -rf $(OBJECT)

fclean: clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: re clean fclean 
