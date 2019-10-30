# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: celva <celva@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 12:08:40 by dkathlee          #+#    #+#              #
#    Updated: 2019/10/30 13:17:14 by celva            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCDIR = srcs/
INCDIR = includes/
OBJDIR = obj/

SRCS =	main.c reader.c hooks.c drawing.c transform.c \

OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

CC = gcc
CFLAGS = 

MLXDIR = mlx/
MLXLIB = $(addprefix $(MLXDIR), mlx.a)
MLXINC = -I $(MLXDIR)
MLXLNK = -L $(MLXDIR) -l mlx -framework OpenGL -framework AppKit

FTDIR = libft/
FTLIB = $(addprefix $(FTDIR), libft.a)
FTINC = -I $(FTDIR)/includes
FTLNK = -L $(FTDIR) -l ft

all: obj $(FTLIB) $(MLXLIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(MLXINC) $(FTINC) -I $(INCDIR) -o $@ -c $<

$(FTLIB):
	make -C $(FTDIR)

$(MLXLIB):
	make -sC $(MLXDIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLXLNK) $(FTLNK) -lm -o $(NAME)

linux:
	gcc -o q $(addprefix $(SRCDIR), $(SRCS)) $(FTLIB) -I $(INCDIR) $(MLXINC) $(FTINC) mlx_linux/libmlx_Linux.a -lm -lXext -lX11

clean:
	rm -rf $(OBJDIR)
	make -C $(FTDIR) clean
	make -C $(MLXDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FTDIR) fclean

re: fclean all

.PHONY: clean fclean all re
