# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 16:56:33 by hmrabet           #+#    #+#              #
#    Updated: 2024/04/23 06:12:53 by hmrabet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BONUS = minishell_bonus

SRCS = main.c init_data.c \
		heap/heap.c \
		utils/utils-0.c utils/utils-1.c utils/utils-2.c utils/splitpaths.c \
		env/env.c \
		signals/signals.c \
		lexer/lexer-0.c lexer/lexer-1.c lexer/lexer-2.c lexer/lexer-3.c

OBJS = $(SRCS:.c=.o)

CC = cc -Wall -Wextra -Werror
RM = rm -f
INCLUDES = -Iincludes
READLINE_LIB = -lreadline #-L/Users/hmrabet/.brew/opt/readline/lib
# READLINE_INC = -I/Users/hmrabet/.brew/opt/readline/include

all : $(NAME)
	
$(NAME) : $(OBJS)
	$(CC) $(READLINE_LIB) $^ -o minishell

%.o : %.c  includes/minishell.h Makefile
	$(CC) $(INCLUDES) -c $< -o $@
	
clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME) $(BONUS)

re : fclean all

.PHONY : clean
