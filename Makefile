# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 16:56:33 by hmrabet           #+#    #+#              #
#    Updated: 2024/08/25 19:37:01 by hmrabet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BONUS = minishell_bonus

SRCS = main.c init_data.c exit_status.c \
		utils/heap.c utils/utils-0.c utils/utils-1.c utils/utils-2.c utils/utils-3.c utils/utils-4.c utils/utils-5.c utils/splitpaths.c utils/ft_split_local.c utils/ft_split_global.c \
		env/init_env.c env/get_env.c env/set_env.c env/remove_env.c env/env_utils.c \
		signals/signals-0.c signals/signals-1.c \
		lexer/lexer-0.c lexer/lexer-1.c lexer/lexer-2.c lexer/lexer-3.c lexer/lexer-4.c lexer/here_doc_err.c lexer/validate_format.c lexer/check_op_syntax.c \
		parser/parser-0.c parser/parser-1.c parser/parser-2.c parser/expanding.c parser/expanding-text.c parser/expanding-quotes.c parser/wildcards.c parser/wildcard_match_pattern.c \
		execution/heredoc.c \
		execution/builtins/builtins.c \
		execution/builtins/cd.c \
		execution/builtins/exit.c \
		execution/builtins/echo.c \
		execution/builtins/env.c \
		execution/builtins/export-0.c \
		execution/builtins/export-1.c \
		execution/builtins/pwd.c \
		execution/builtins/unset.c \
		build_tree/build_tree-0.c build_tree/build_tree-1.c build_tree/build_tree-2.c build_tree/execute_node.c build_tree/helper.c \
		execution/prepare_exec.c \
		execution/execute_all.c \
		execution/execution_utils.c \
		execution/iofiles_checker.c \
		execution/ft_get_path.c \
		execution/file_descriptors.c \
		execution/run_command.c \

OBJS = $(SRCS:.c=.o)

CC = cc -Wall -Wextra -Werror #-g -fsanitize=address
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
