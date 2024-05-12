# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 16:56:33 by hmrabet           #+#    #+#              #
#    Updated: 2024/05/12 12:00:56 by hmrabet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BONUS = minishell_bonus

SRCS = main.c init_data.c exit_status.c \
		utils/heap.c utils/utils-0.c utils/utils-1.c utils/utils-2.c utils/utils-3.c utils/splitpaths.c utils/ft_split.c \
		env/init_env.c env/get_env.c env/set_env.c env/remove_env.c env/utils.c \
		signals/signals.c \
		lexer/lexer-0.c lexer/lexer-1.c lexer/lexer-2.c lexer/lexer-3.c \
		parser/parser-0.c parser/expanding.c parser/wildcards.c \
		execution/heredoc.c execution/execution.c \
		execution/builtins/builtins.c execution/builtins/cd.c execution/builtins/echo.c execution/builtins/env.c execution/builtins/export-0.c execution/builtins/export-1.c execution/builtins/pwd.c execution/builtins/unset.c \

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
