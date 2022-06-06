#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 10:59:36 by gtoubol           #+#    #+#              #
#    Updated: 2022/06/06 16:39:14 by gtoubol          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# List of all the sources (.c)
# -------------------------------------------------------------------------
SRCS = 		pp_fullname.c pp_get_path.c pp_read_file.c pp_write_file.c		\
			pp_process_read.c pp_process_write.c pp_process_exec.c
VANILLA =	pipex.c
BONUS = pipex_bonus.c pp_read_heredoc.c pp_write_file_append.c	\
			pp_process_read_bonus.c pp_read_file_bonus.c			\
			pp_process_write_bonus.c pp_heredoc.c

# List of the related directories
# -------------------------------------------------------------------------
SRCS_DIR =	srcs
HEAD_DIR =	includes libft/includes

# List of all compilation options
# -------------------------------------------------------------------------
CC = 		gcc
CFLAGS =	-Wall -Wextra
CDEBUG =	-g3
CRELEASE =	-Werror
CPROFILE =	-pg

# Description of the final target
# -------------------------------------------------------------------------
NAME =		pipex
NAME_B = 	pipex_bonus

# Libraries
# -------------------------------------------------------------------------
LIBFT_DIR = libft
LIBFT =		libft/libft.a
LIB =		-Llibft -lft

# General rules on makefile
# -------------------------------------------------------------------------
OBJS = 		$(addprefix $(SRCS_DIR)/,$(SRCS:.c=.o) $(VANILLA:.c=.o))
OBJS_B =	$(addprefix $(SRCS_DIR)/,$(SRCS:.c=.o) $(BONUS:.c=.o))
DEPS =		$(OBJS:.o=.d) $(OBJS_B:.o=.d)

INCLUDES =	$(addprefix -I,$(HEAD_DIR))

ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CFLAGS += $(CDEBUG)
else ifeq (profile, $(filter profile,$(MAKECMDGOALS)))
	CFLAGS += $(CPROFILE) $(CRELEASE)
else
	CFLAGS += $(CRELEASE)
endif
RM =		rm -f

vpath %.c $(SRCS_DIR)
vpath %.h $(HEAD_DIR)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIB)


$(NAME_B):	$(OBJS_B) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS_B) $(LIB)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $< $(LIB)

all:		$(NAME)

bonus:		$(NAME_B)

clean:		dclean
			$(RM) $(OBJS) $(OBJS_B)

fclean:		clean libfclean
			$(RM) $(NAME) $(NAME_B)

re:			fclean all

.PHONY:		all clean fclean re bonus

# Library rules
# -----------------------------------------------------------------------
$(LIBFT):	libft.h
			$(MAKE) -C $(LIBFT_DIR)

libclean:
			$(MAKE) -C $(LIBFT_DIR) clean

libfclean:
			$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY:		libclean libfclean

# Custom rules
# ------------------------------------------------------------------------
debug:		all
profile:	all
			@echo "\e[36mTo use profiler:"
			@echo "    1. Run your app"
			@echo "    2. grof \e[3m<your-app>\e[0;36m gmon.out > \e[3m<analysis-file>\e[0;36m"
			@echo "    3. cat \e[3m<analysis-file>\e[0m"

.PHONY:		debug profile

# General dependences management
# ------------------------------------------------------------------------
%.d:		%.c
			$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $(INCLUDES) $< $(LIB) > $@

dclean:
			$(RM) $(DEPS)

.PHONY:		dclean
.SILENT:    $(DEPS) dclean

-include	$(DEPS)
