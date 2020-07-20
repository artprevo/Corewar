# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artprevo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 18:16:55 by artprevo          #+#    #+#              #
#    Updated: 2020/01/13 17:41:52 by artprevo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm
CC = gcc
CFLAGS = 
SRCS = main.c print.c \
fetch_label.c fetch_champ.c fetch_actions_op.c fetch_param.c fetch_param_tools.c \
struct_add.c struct_init.c ft_error.c weight_and_size.c \
process_ocp.c write_header.c write_champ.c write_tools.c tools.c

OBJS_PATH = objs/
SRCS_PATH = srcs/
OBJS = $(patsubst %.c, $(OBJS_PATH)%.o, $(SRCS))
LIBFT = libft/libft.a
HEADER = ./includes/asm.h ./libft/libft.h
INCLUDES = -I ./includes/ -I ./libft/

all: $(LIBFT) $(OBJS_PATH) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	printf "\033[0;36m> Compiling asm\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -Llibft/ -lft $^ -o $@
	printf "\033[0;32m OK\n\033[0m"

$(OBJS): $(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_PATH):
	mkdir $@

$(LIBFT): FORCE
	$(MAKE) -C libft/

FORCE:

clean:
	$(RM) -R $(OBJS_PATH)
	$(MAKE) -C libft/ clean

fclean: clean
	$(MAKE) -C libft/ fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
.SILENT:
