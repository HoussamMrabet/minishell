/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:52:05 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/20 09:59:53 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "heap.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <paths.h>

typedef struct s_tokenizer
{
	char				*token;
	int					type;
	struct s_tokenizer	*next;
}	t_tokenizer;

typedef struct s_minishell
{
	char			**env;
	t_block_memory	*garbage;
}	t_minishell;

// utils
size_t	ft_strlen(const char *s);
size_t	ft_arrlen(char **arr);
char	*ft_strjoin(char *s1, char *s2, t_block_memory **garbage);
char	*ft_strdup(char *s1, t_block_memory **garbage);
void	ft_putstr_fd(char *s, int fd);

// env
void	init_default_env(t_minishell *minishell, char **env);
void	init_custom_env(t_minishell *minishell);

// signals
void	handle_sigint(int signal);

#endif