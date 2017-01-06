NAME = libft.a

SRC = ft_atoi.c \
	  ft_bzero.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_islower.c \
	  ft_isprint.c \
	  ft_ispunct.c \
	  ft_isspace.c \
	  ft_isupper.c \
	  ft_memccpy.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_strcat.c \
	  ft_strchr.c \
	  ft_strcmp.c \
	  ft_strcpy.c \
	  ft_strdup.c \
	  ft_strlcat.c \
	  ft_strlen.c \
	  ft_strncat.c \
	  ft_strncmp.c \
	  ft_strncpy.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_strstr.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_memalloc.c \
	  ft_memdel.c \
	  ft_strnew.c \
	  ft_strdel.c \
	  ft_strclr.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strequ.c \
	  ft_strnequ.c \
	  ft_strsub.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_strsplit.c \
	  ft_itoa.c \
	  ft_putchar.c \
	  ft_putstr.c \
	  ft_putendl.c \
	  ft_putnbr.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_lstnew.c \
	  ft_lstdelone.c \
	  ft_lstdel.c \
	  ft_classicfree.c \
	  ft_lstadd.c \
	  ft_lstpushback.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_lstcount.c \
	  ft_lstat.c \
	  ft_putbinary.c \
	  ft_pow.c \
	  ft_sqrt.c \
	  ft_get_next_line.c

OBJECTS = $(SRC:.c=.o)

FT_PRINTF_OBJS = $(addprefix ft_printf/, $(shell make -s -C ft_printf list))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJECTS)
		make -C ft_printf
		ar rcs $(NAME) $(OBJECTS) $(FT_PRINTF_OBJS)

clean:
		make -C ft_printf clean
		rm -rf $(OBJECTS)

fclean: clean
		rm -rf $(NAME)

re: fclean all
