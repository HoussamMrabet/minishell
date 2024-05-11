/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:52:05 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/11 20:20:44 by hmrabet          ###   ########.fr       */
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

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef enum e_type
{
	CMD,
	TEXT,
	PIPE,
	OR,
	AND,
	IN_RED,
	OUT_RED,
	DELIMITER,
	DELIM,
	APPEND,
	SPACES,
	S_QUOTE,
	D_QUOTE,
	PARENTHESE,
	WILD_CARD,
}	t_type;

typedef struct s_tokenizer
{
	char				*token;
	t_type				type;
	struct s_tokenizer	*next;
}	t_tokenizer;

typedef struct s_cmdlist
{
	t_tokenizer			*tokens;
	t_type				type;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_minishell
{
	char			**env;
	char			**fake_env;
	t_bool			custom_env;
	char			**paths;
	int				lvl;
	t_tokenizer		*tokens;
	t_cmdlist		*cmdlist;
	t_block_memory	*global;
	t_block_memory	*local;
}	t_minishell;

// utils
size_t	ft_strlen(const char *s);
size_t	ft_arrlen(char **arr);
char	*ft_strjoin(char *s1, char *s2, t_block_memory **garbage);
char	*ft_strdup(char *s1, t_block_memory **garbage);
char	*ft_substr(t_block_memory **g, char *s, unsigned int start, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
t_bool	is_equal(char *str1, char *str2);
int		ft_exit(char *msg, int status, t_minishell *minishell);
int		ft_atoi(char *str);
char	*ft_itoa(t_block_memory **garbage, int n);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
t_bool	ft_strchr(char *s, char c);
t_bool	ft_isalnum(char c);
t_bool	ft_isal(char c);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char *s, char c, t_block_memory **garbage);

// env
void	init_default_env(t_minishell *minishell, char **env);
void	init_custom_env(t_minishell *minishell);
void	set_env_value(t_minishell *minishell, char *env, char *value);
void	set_fake_env_value(t_minishell *minishell, char *env, char *value);
char	*get_env_value(t_minishell *minishell, char *str);

// signals
void	handle_sigint(int signal);

// init data
void	init_data(t_minishell *minishell, char **env);
char	**splitpaths(char *s, char c, t_block_memory **garbage);

// lexer
int		lexer(t_minishell *minishell, char *input);
int		syntax_invalid(char *input);
void	handle_commands(t_minishell *m, t_tokenizer **t, char *s, int *i);
void	handle_single_quotes(t_minishell *s, t_tokenizer **t, char *n, int *i);
void	handle_double_quotes(t_minishell *m, t_tokenizer **t, char *s, int *i);
void	handle_red_and_del(t_minishell *m, t_tokenizer **t, char *s, int *i);
void	handle_paranthese(t_minishell *m, t_tokenizer **t, char *s, int *i);
void	handle_pipe_or_sign(t_minishell *m, t_tokenizer **t, char *s, int *i);
void	handle_and_sign(t_minishell *m, t_tokenizer **t, char *s, int *i);
void	handle_spaces(t_minishell *m, t_tokenizer **t, char *s, int *i);
void	add_token(t_tokenizer **tokens, t_tokenizer *new);
int		check_op_syntax(t_minishell *minishell);

// parser
void	parser(t_minishell *minishell);
void	remove_quotes(t_minishell *minishell, char **tokens, char sign);
void	ft_wildcards(t_minishell *minishell);
void	merge_wildcards(t_minishell *minishell);

// expanding
void	replace_expand_values(t_minishell *minishell, t_tokenizer **tokens);

// exit
int		exit_status(int new_status, t_bool to_set);

// builtins
int		check_builtins(t_minishell *minishell, char *cmd);
char	*ft_echo(t_minishell *minishell, char *cmd);
char	*ft_pwd(t_minishell *minishell);
char	*ft_env(t_minishell *minishell);
void	ft_export(t_minishell *minishell, char *cmd);

// execution
void	run_commands(t_minishell *minishell);
void	here_doc(t_minishell *minishell);

#endif
