# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <jubarbie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/30 16:51:35 by jubarbie          #+#    #+#              #
#    Updated: 2016/11/08 12:44:58 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -ILibs/libft -ILibs/libmlx -ILibs/libv3d -IIncludes -Wall -Wextra -Werror
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
	@make -C Libs/libv3d
	@make -C Libs/libmlx
	@$(CC) -LLibs/libft/ -lft -LLibs/libmlx/ -lmlx -LLibs/libv3d/ -lv3d -framework OpenGL -framework AppKit -framework Opencl -o $@ $^
	@echo "\033[32m[OK]\033[0m rtv1 created"

all: $(NAME)
	
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@make clean -C Libs/libft
	@make clean -C Libs/libv3d
	@rm -rf $(OBJDIR)
	@echo "\033[32m[OK]\033[0m object files deleted"

fclean: clean
	@make fclean -C Libs/libft
	@make fclean -C Libs/libv3d
	@make clean -C Libs/libmlx
	@rm -rf $(NAME)
	@echo "\033[32m[OK]\033[0m rtv1 deleted"

re: fclean all
