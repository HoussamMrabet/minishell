/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:52:05 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/20 14:21:09 by hmrabet          ###   ########.fr       */
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
# include <stdio.h>

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_tokenizer
{
	char				*token;
	int					type;
	struct s_tokenizer	*next;
}	t_tokenizer;

typedef struct s_minishell
{
	char			**env;
	char			**paths;
	t_block_memory	*garbage;
}	t_minishell;

// utils
size_t	ft_strlen(const char *s);
size_t	ft_arrlen(char **arr);
char	*ft_strjoin(char *s1, char *s2, t_block_memory **garbage);
char	*ft_strdup(char *s1, t_block_memory **garbage);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
t_bool	is_equal(char *str1, char *str2);
void	ft_exit(char *msg, int status, t_block_memory **garbage);
char	**ft_split(const char *s, char c, t_block_memory **garbage);

// env
void	init_default_env(t_minishell *minishell, char **env);
void	init_custom_env(t_minishell *minishell);
char	*get_env_value(t_minishell *minishell, char *str);

// signals
void	handle_sigint(int signal);

// init data
void	init_data(t_minishell *minishell, char **env);
char	**splitpaths(char *s, char c, t_block_memory **garbage);

#endif