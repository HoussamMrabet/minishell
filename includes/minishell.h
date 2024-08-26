/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:52:05 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/26 17:42:18 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <limits.h>
# include <sys/errno.h>

# define SYNTAX_MSG "minishell: syntax error near unexpected token "
# define CD_ERR_MSG1 "cd: error retrieving current directory: getcwd: cannot "
# define CD_ERR_MSG2 "access parent directories: No such file or directory\n"

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
	DEL,
	DELIM,
	APPEND,
	SPACES,
	S_QUOTE,
	D_QUOTE,
	PAR,
	WILD_CARD,
	Q_DELIM,
	EXPAND,
}	t_type;

typedef struct s_block_memory
{
	void					*leak;
	struct s_block_memory	*next;
}	t_block_memory;

typedef struct s_iofiles
{
	char				*token;
	t_bool				amb;
	t_type				type;
	struct s_iofiles	*next;
}	t_iofiles;

typedef struct s_tokenizer
{
	char				*token;
	t_type				type;
	unsigned int		lvl;
	t_bool				amb;
	t_bool				is_expand;
	int					chain;
	struct s_tokenizer	*next;
	struct s_tokenizer	*last;
}	t_tokenizer;

typedef struct s_exec
{
	t_tokenizer			*tokens;
	t_type				type;
	t_iofiles			*iofiles;
	int					fdin;
	int					fdout;
	t_bool				is_pipe;
	struct s_exec		*left;
	struct s_exec		*right;
}	t_exec;

typedef struct s_syntax_err
{
	char	*msg;
	int		pos;
}	t_syntax_err;

typedef struct s_minishell
{
	char				*input;
	char				**env;
	char				**fake_env;
	t_bool				custom_env;
	char				**paths;
	char				*home;
	char				*_;
	char				*pwd;
	int					lvl;
	int					max_fd;
	t_syntax_err		err;
	t_tokenizer			*tokens;
	t_exec				*tree;
	t_block_memory		*global;
	t_block_memory		*local;
	struct termios		termios;
}	t_minishell;

typedef struct s_pids_list
{
	pid_t				pid;
	struct s_pids_list	*next;
}	t_pids_list;

typedef unsigned long long	t_atoul;

// utils
size_t		ft_strlen(const char *s);
size_t		ft_arrlen(char **arr);
char		*ft_strjoin(char *s1, char *s2, t_minishell *m, t_block_memory **g);
char		*ft_strdup(char *s1, t_minishell *m, t_block_memory **g);
char		*ft_substr(t_minishell *m,
				char *s, unsigned int st, size_t l);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
t_bool		is_equal(char *str1, char *str2);
int			ft_exit(char *msg, int status, t_minishell *minishell);
void		ft_exit_builtin(t_minishell *m, t_exec *tree);
int			ft_atoi(char *str);
t_atoul		ft_atoul(char *str);
char		*ft_itoa(t_minishell *minishell, t_block_memory **garbage, int n);
size_t		ft_strlcat(char *dst, char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
t_bool		ft_strchr(char *s, char c);
t_bool		ft_isalnum(char c);
t_bool		ft_isal(char c);
int			ft_strcmp(char *s1, char *s2);
char		**ft_split_local(char *s, char c, t_minishell *m);
char		**ft_split_global(char *s, char c, t_minishell *m);
t_tokenizer	*token_dup(t_minishell *minishell, t_tokenizer *token);
void		close_fds(t_minishell *minishell);
char		*ft_strtrim(t_minishell *mini, char *s1, char *set);
void		reverse_str(char **str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(char *haystack, char *needle, size_t len);

// env
void		init_default_env(t_minishell *minishell, char **env);
void		init_custom_env(t_minishell *minishell);
void		set_env_value(t_minishell *minishell, char *env, char *value);
void		set_fake_env_value(t_minishell *minishell, char *env, char *value);
char		*get_env_value(t_minishell *minishell, char *str);
void		remove_fake_env(t_minishell *minishell, char *var);
void		remove_env(t_minishell *minishell, char *var);
int			starts_with(char *s1, char *s2);
void		sort_env(char **env);

// signals
void		child_minishell_handler(int signal);
void		child_handler(int signal);
void		handle_sigint(int signal);
void		heredoc_signal(int signal);
int			heredoc_status(int new_stat, t_bool to_set);
void		handle_quit(int signal);
void		signals_handle(t_minishell *mini, t_exec *tree);

// init data
void		init_data(t_minishell *minishell, char **env);
char		**splitpaths(char *s, char c, t_minishell *m);

// lexer
int			lexer(t_minishell *minishell, char *input);
int			syntax_invalid(t_minishell *minishell, char *input);
int			between_parenth(t_minishell *m, char *input, int *i);
void		handle_commands(t_minishell *m, t_tokenizer **t, char *s, int *i);
void		handle_single_quotes(t_minishell *s, t_tokenizer **t,
				char *n, int *i);
void		handle_double_quotes(t_minishell *m, t_tokenizer **t,
				char *s, int *i);
void		handle_red_and_del(t_minishell *m, t_tokenizer **t,
				char *s, int *i);
void		handle_paranthese(t_minishell *m, t_tokenizer **t, char *s, int *i);
void		handle_pipe_or_sign(t_minishell *m, t_tokenizer **t,
				char *s, int *i);
void		handle_and_sign(t_minishell *m, t_tokenizer **t, char *s, int *i);
void		handle_spaces(t_minishell *m, t_tokenizer **t, char *s, int *i);
void		add_token(t_tokenizer **tokens, t_tokenizer *new);
int			check_op_syntax(t_minishell *minishell);
void		here_doc_err(t_minishell *minishell, char *input);
t_bool		format_invalid(t_minishell *m, char *input);

// parser
int			parser(t_minishell *minishell);
void		merge_delimiters(t_minishell *m, t_tokenizer **tokens);
void		remove_quotes(t_minishell *minishell, char **tokens, char sign);

// expanding
void		replace_expand_values(t_minishell *minishell, t_tokenizer **tokens);
void		handle_quote_expand(t_minishell *minishell, char **tokens);
void		handle_text_expand(t_minishell *m, t_tokenizer *t, char **ts);

// exit
int			exit_status(int new_status, t_bool to_set);

// builtins
int			check_builtins(t_minishell *minishell, t_exec *tree);
void		ft_echo(t_minishell *m, t_exec *tree);
void		ft_pwd(t_minishell *minishell, t_exec *tree);
void		ft_env(t_minishell *minishell, t_exec *tree);
void		ft_export(t_minishell *m, t_exec *tree);
void		handle_export(t_exec *tree, t_minishell *m, char **i);
void		ft_unset(t_minishell *minishell, t_exec *tree);
void		ft_cd(t_minishell *minishell, t_exec *tree);

// tree builders
int			here_doc(t_minishell *minishell);
void		build_tree(t_minishell *m, t_exec **t, unsigned int c);
void		split_tree_tokens(t_minishell *mini, t_exec **tree,
				t_type type, unsigned int current_lvl);

// execution helpers
void		prepare_node_for_execute(t_minishell *minishell, t_exec *node);
void		merge_tokens(t_minishell *minishell, t_tokenizer **tokens);
void		split_commands(t_minishell *m, t_tokenizer **tokens);
void		ft_wildcards(t_minishell *minishell, t_tokenizer **token);
t_bool		file_match(t_minishell *mi, char *pattern, char *filename);
void		separate_wildcards(t_tokenizer **tokens);
void		merge_wildcards(t_minishell *minishell, t_tokenizer **token);
void		set_io_tokens(t_minishell *m, t_exec **tree);
void		check_ambiguous(t_minishell *minishell, t_tokenizer **tokens);
void		set_loadash(t_minishell *minishell, t_exec *node);

// custom functions
void		*ft_readline(t_minishell *minishell, char *input, t_bool add);
void		*ft_getcwd(t_minishell *minishell);

// HEAP
void		*ft_malloc(t_minishell *m, t_block_memory **g, size_t s);
void		ft_free(t_block_memory **memory);
void		ft_free_all(t_minishell *minishell);

// execution
int			run_command(t_exec *tree, t_minishell *mini);
int			execute_all(t_exec *tree, t_minishell *mini);
void		add_pipes(t_exec *tree, int sdin, int sdout, t_minishell *mini);
char		**to_array(t_tokenizer *tokens, t_minishell *mini);
void		wait_all(pid_t pid);
void		execute_one(t_exec *tree, t_minishell *mini, t_pids_list **pids);
t_pids_list	*create_one_pid(t_minishell *mini, t_pids_list **pids, pid_t pid);
void		close_fds_child(t_minishell *m, int fdin, int fdout, t_exec *tree);
void		catch_error(t_minishell *m, int i, char *command);
int			tokens_length(t_tokenizer *tokens);
void		open_files(t_minishell *mini, t_exec *tree);
void		check_ambig(t_minishell *mini, t_bool val, char *str);
void		open_append(t_minishell *mini, t_exec *tree, int *fdout);
void		open_rdout(t_minishell *mini, t_exec *tree, int *fdout);
void		open_rdin(t_minishell *mini, t_exec *tree, int *fdin);
char		*ft_get_path(t_minishell *mini, t_tokenizer *tokens);
void		signals_handle(t_minishell *mini, t_exec *tree);
void		process_code(t_exec *tree, t_minishell *mini);
void		close_sibling_fd(t_exec *tree);
void		fun_error(t_minishell *mini, int i, char *str);
int			close_fds_child_btn(int fdin, int fdout, t_exec *tree);
void		catch_error_builtin(int i, char *command);
int			open_files_builtin(t_exec *tree);
int			open_rdin_bultin(t_exec *tree, int *fdin);
int			open_rdout_builtin(t_exec *tree, int *fdout);
int			open_append_builtin(t_exec *tree, int *fdout);
int			check_ambig_builtin(t_bool val, char *str);
#endif
