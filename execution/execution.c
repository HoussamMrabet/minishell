/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:13:57 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/11 19:46:01 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executer(t_minishell *minishell, char *cmd, char **args)
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

void 	execute_cmd(t_minishell *minishell, char *cmd)
{
	char	**splited;
	char	**secure_paths;
	int		i;
	t_bool	found;
	
	i = 0;
	found = FALSE;
	splited = ft_split(cmd, '\n', &minishell->local);
	secure_paths = minishell->paths;
	while (secure_paths[i] && splited[0][0] != '/')
	{
		cmd = ft_strjoin(secure_paths[i], splited[0], &minishell->local);
		if (!access(cmd, X_OK))
		{
			found = TRUE;
			exit_status(executer(minishell, cmd, splited), TRUE);
			break ;
		}
		i++;
	}
	if (!found)
	{
		if (ft_strchr(splited[0], '/') && splited[0][ft_strlen(splited[0]) - 1] != '/')
		{
			if (splited[0][0] != '/')
			{
				cmd = ft_strjoin(get_env_value(minishell, "PWD"), "/", &minishell->local);
				cmd = ft_strjoin(cmd, splited[0], &minishell->local);
			}
			if (!found && !access(cmd, X_OK))
			{
				found = TRUE;
				exit_status(executer(minishell, cmd, splited), TRUE);
			}
			else
				printf("minishell: %s: command not found\n", cmd);			
		}
		else
			printf("minishell: %s: command not found\n", splited[0]);			

	}
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
