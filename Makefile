# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <jubarbie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/30 16:51:35 by jubarbie          #+#    #+#              #
#    Updated: 2016/11/07 14:48:27 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -ILibs/libft -ILibs/libmlx -IIncludes -Wall -Wextra -Werror
SRC=	rtv1.c			\
		color.c			\
		options.c		\
		error.c			\
		key_event.c		\
		env.c			\
		vector.c		\
		vector2.c		\
		debug.c			\
		parse.c			\
		parse_obj.c		\
		raytracer.c		\
		sphere.c		\
		plane.c			\
		cylinder.c		\
		moves.c
OBJDIR=Objects
VPATH=Sources
OBJS=$(patsubst %,$(OBJDIR)/%,$(SRC:.c=.o))
NAME=rtv1

$(NAME): $(OBJS)
	@make -C Libs/libft
	@make -C Libs/libmlx
	@$(CC) -LLibs/libft/ -lft -LLibs/libmlx/ -lmlx -framework OpenGL -framework AppKit -framework Opencl -o $@ $^
	@echo "\033[32m[OK]\033[0m rtv1 created"

all: $(NAME)
	
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@make clean -C Libs/libft
	@rm -rf $(OBJDIR)
	@echo "\033[32m[OK]\033[0m object files deleted"

fclean: clean
	@make fclean -C Libs/libft
	@make clean -C Libs/libmlx
	@rm -rf $(NAME)
	@echo "\033[32m[OK]\033[0m rtv1 deleted"

re: fclean all
