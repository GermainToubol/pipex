#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 10:59:36 by gtoubol           #+#    #+#              #
#    Updated: 2022/05/31 12:20:01 by gtoubol          ###   ########.fr        #
#                                                                              #
#******************************************************************************#
SRCS =		pipex.c pp_fullname.c
OBJS = 		$(SRCS:.c=.o)
DEPS =		$(SRCS:.c=.d)

NAME = 		pipex

LIBFT_DIR = libft
LIBFT =		libft/libft.a
LIB =		-Llibft -lft

CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror
INCLUDES = 	-I./libft
RM =		rm -f

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIB)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.d:		%.c
			@set -e; rm -f $@;												\
			$(CC) -MM $(CFLAGS) $(INCLUDES) $< > $@.$$$$;					\
			sed 's,\($*\)\.	o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;			\
			rm -f $@.$$$$

bonus:		all

$(LIBFT):
			make -C $(LIBFT_DIR)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(DEPS)
			make -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			make -C $(LIBFT_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re bonus

include		$(DEPS)
