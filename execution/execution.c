/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:13:57 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 19:21:22 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	executer(t_minishell *minishell, char *cmd, char **args)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, args, minishell->env);
		perror("");
		return (1);
	}
	waitpid(pid, &status, 0);
	return (status);
}

static void	not_found_cmd(t_minishell *m, char *cmd, char **sp, t_bool found)
{
	if (ft_strchr(sp[0], '/')
		&& sp[0][ft_strlen(sp[0]) - 1] != '/')
	{
		if (sp[0][0] != '/')
		{
			cmd = ft_strjoin(get_env_value(m, "PWD"),
					"/", m, &m->local);
			cmd = ft_strjoin(cmd, sp[0], m, &m->local);
		}
		if (!found && !access(cmd, X_OK))
		{
			found = TRUE;
			exit_status(executer(m, cmd, sp), TRUE);
		}
		else
			printf("minishell: %s: command not found\n", cmd);
	}
	else
		printf("minishell: %s: command not found\n", sp[0]);
}

static void	execute_cmd(t_minishell *m, char *cmd)
{
	char	**splited;
	char	**secure_paths;
	int		i;
	t_bool	found;

	(1) && (i = 0, found = FALSE, splited = ft_split_local(cmd, '\n', m));
	secure_paths = m->paths;
	while (secure_paths[i] && splited[0][0] != '/')
	{
		cmd = ft_strjoin(secure_paths[i], splited[0], m, &m->local);
		if (!access(cmd, X_OK))
		{
			found = TRUE;
			exit_status(executer(m, cmd, splited), TRUE);
			break ;
		}
		i++;
	}
	if (!found)
		not_found_cmd(m, cmd, splited, found);
}

void	run_commands(t_minishell *minishell)
{
	t_tokenizer	*tokens;

	here_doc(minishell);
	tokens = minishell->tokens;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			if (check_builtins(minishell, tokens->token))
				execute_cmd(minishell, tokens->token);
		}
		tokens = tokens->next;
	}
}
