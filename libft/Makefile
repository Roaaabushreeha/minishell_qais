CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

ARFLAGS = rcs

SRCS = ft_itoa.c  \
	ft_split.c \
	ft_putstr_fd.c  \
	ft_putendl_fd.c ft_putchar_fd.c ft_putnbr_fd.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_strdup.c ft_calloc.c\
	ft_isalpha.c ft_bzero.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strlen.c ft_memcpy.c  ft_memset.c\
	ft_strlcat.c ft_strlcpy.c ft_tolower.c ft_toupper.c ft_strncmp.c ft_strnstr.c ft_memmove.c ft_strchr.c ft_strrchr.c \
	ft_memchr.c ft_memcmp.c ft_atoi.c ft_printf.c check_func.c check_funcc.c ft_striteri.c ft_strmapi.c get_next_line.c get_next_line_utils.c ft_strndup.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

#here we rebuild everything, by deleting and redoing all of the steps again
re: fclean all


.PHONY: all clean fclean re
