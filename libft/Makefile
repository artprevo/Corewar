# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 00:20:03 by artprevo          #+#    #+#              #
#    Updated: 2020/07/31 15:55:52 by artprevo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a
FLAGS = 
SRC = ft_strjoinf.c				\
	get_next_line.c				\
	ft_memccpy.c    			\
	ft_memmove.c     			\
	ft_memchr.c      			\
	ft_memcpy.c      			\
	ft_memset.c		 			\
	ft_memcmp.c					\
	ft_memalloc.c				\
	ft_memdel.c					\
	ft_atoi.c        			\
	ft_bzero.c        			\
	ft_tolower.c    			\
	ft_toupper.c				\
	ft_itoa.c					\
	ft_lstnew.c				\
	ft_lstdelone.c				\
	ft_lstdel.c					\
	ft_lstadd.c					\
	ft_lstiter.c				\
	ft_lstmap.c					\
	ft_isalnum.c   		 		\
	ft_isalpha.c    			\
	ft_isascii.c    			\
	ft_isdigit.c    			\
	ft_isprint.c				\
	ft_putchar.c  		  		\
	ft_putstr.c        			\
	ft_putendl.c    			\
	ft_putnbr.c					\
	ft_putchar_fd.c				\
	ft_putstr_fd.c				\
	ft_putendl_fd.c				\
	ft_putnbr_fd.c				\
	ft_strlen.c   	     		\
	ft_strdup.c        			\
	ft_strcpy.c        			\
	ft_strncpy.c    			\
	ft_strcat.c        			\
	ft_strncat.c    			\
	ft_strlcat.c    			\
	ft_strstr.c        			\
	ft_strnstr.c    			\
	ft_strchr.c        			\
	ft_strrchr.c    			\
	ft_strcmp.c        			\
	ft_strncmp.c    			\
	ft_strequ.c        			\
	ft_strnequ.c    			\
	ft_strmap.c        			\
	ft_strmapi.c    			\
	ft_striter.c    			\
	ft_striteri.c    			\
	ft_strnew.c        			\
	ft_strdel.c        			\
	ft_strclr.c					\
	ft_strsub.c					\
	ft_strjoin.c				\
	ft_strtrim.c				\
	ft_strsplit.c				\
	ft_fibonacci.c				\
	ft_find_next_prime.c		\
	ft_is_prime.c				\
	ft_recursive_factorial.c	\
	ft_recursive_power.c		\
	ft_sqrt.c					\
	ft_stristr.c				\
	ft_perror.c					\
	ft_strjoinf_l.c				\
	ft_itoabase.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	printf "\033[0;36m> Compiling libft\033[0m"
	ar rc $(NAME) $(OBJS)
	printf "\033[0;32m OK\n\033[0m"


$(OBJS): %.o: %.c
	gcc $(FLAGS) -c $< -I /libft.h -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
