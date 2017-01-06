# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/19 17:03:14 by mhammerc          #+#    #+#              #
#    Updated: 2016/12/08 14:08:44 by mhammerc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra 
CC = gcc

SRCS = parse.c \
	   parse1.c \
	   register_printf_function.c \
	   search_conversion.c \
	   ft_printf.c \
	   wide_char.c \
	   conversions/printf_print_decimal_signed.c \
	   conversions/printf_print_decimal_unsigned.c \
	   conversions/printf_print_hexadecimal.c \
	   conversions/printf_print_octal.c \
	   conversions/printf_print_percentage.c \
	   conversions/printf_print_char.c \
	   conversions/printf_print_string.c \
	   conversions/printf_print_pointer.c

OBJS = $(SRCS:.c=.o)

all: $(OBJS) 

list:
	@echo $(OBJS)

clean:
	rm -f $(OBJS)

re: clean all
