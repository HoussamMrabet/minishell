# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 16:56:33 by hmrabet           #+#    #+#              #
#    Updated: 2024/04/20 10:11:44 by hmrabet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BONUS = minishell_bonus

SRCS = main.c heap.c utils-0.c utils-1.c env.c signals.c
OBJS = $(SRCS:.c=.o)

CC = cc -Wall -Wextra -Werror
RM = rm -f
READLINE_LIB = -lreadline #-L/Users/hmrabet/.brew/opt/readline/lib
# READLINE_INC = -I/Users/hmrabet/.brew/opt/readline/include

all : $(NAME)
	
$(NAME) : $(OBJS)
	$(CC) $(READLINE_LIB) $^ -o minishell

%.o : %.c  minishell.h Makefile
	$(CC) -c $< -o $@
	
clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME) $(BONUS)

re : fclean all

.PHONY : clean
