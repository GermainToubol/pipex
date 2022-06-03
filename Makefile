#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 10:59:36 by gtoubol           #+#    #+#              #
#    Updated: 2022/06/03 11:11:47 by gtoubol          ###   ########.fr        #
#                                                                              #
#******************************************************************************#
SRCS_0 =	pp_fullname.c pp_get_path.c pp_process_exec.c pp_write_file.c	\
			pp_read_file.c pp_process_read.c pp_process_write.c
VANILLA_0 =	pipex.c  pp_process_utils.c
BONUS_0 =	pp_write_file_bonus.c pp_read_file_bonus.c pipex_bonus.c		\
			pp_process_utils_bonus.c pp_process_read_bonus.c 				\
			pp_process_write_bonus.c

SRCS =		$(addprefix srcs/,$(SRCS_0))
VANILLA =	$(addprefix srcs/,$(VANILLA_0))
BONUS =		$(addprefix srcs/,$(BONUS_0))

OBJS = 		$(SRCS:.c=.o) $(VANILLA:.c=.o)
OBJS_B =	$(SRCS:.c=.o) $(BONUS:.c=.o)
DEPS =		$(SRCS:.c=.d) $(VANILLA:.c=.d) $(BONUS:.c=.d)

NAME = 		pipex
NAME_B =	pipex_bonus

LIBFT_DIR = libft
LIBFT =		libft/libft.a
LIB =		-Llibft -lft

CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror
INCLUDES = 	-Iincludes
RM =		rm -f

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIB)


$(NAME_B):	$(OBJS_B) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS_B) $(LIB)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.d:		%.c
			@set -e; rm -f $@;												\
			$(CC) -MM $(CFLAGS) $(INCLUDES) $< > $@.$$$$;					\
			sed 's,\($*\)\.	o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;			\
			rm -f $@.$$$$

bonus:		$(NAME_B)

$(LIBFT):
			make -C $(LIBFT_DIR)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(OBJS_B) $(DEPS)
			make -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME) $(NAME_B)
			make -C $(LIBFT_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re bonus test

include		$(DEPS)
