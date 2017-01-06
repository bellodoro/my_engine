# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/06 14:14:25 by mhammerc          #+#    #+#              #
#    Updated: 2017/01/06 15:02:02 by mhammerc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = example

ENGINE_PATH = ../my_engine

all: $(NAME)

SRCS = main.c \
	  splashscreen.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../my_engine

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

make_engine:
	$(info Compiling engine...)
	@$(MAKE) -C $(ENGINE_PATH) 1>/dev/null

clean_engine:
	$(info Cleaning engine...)
	@$(MAKE) -C $(ENGINE_PATH) clean 1>/dev/null

fclean_engine:
	$(info Cleaning engine...)
	@$(MAKE) -C $(ENGINE_PATH) fclean 1>/dev/null

prepare_game:
	$(info Compiling game...)

$(NAME): make_engine prepare_game $(OBJS)
	@gcc $(OBJS) -o $(NAME) -L../my_engine -lme
	$(info Success! Run make start to run the example game.)

start:
	DYLD_LIBRARY_PATH=$(ENGINE_PATH) ./example

clean: clean_engine
	$(info Cleaning game...)
	@rm -rf $(OBJS)

fclean: fclean_engine
	$(info Cleaning game...)
	@rm -rf $(NAME) $(OBJS)

re: fclean all
