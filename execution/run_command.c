/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:11:27 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/08/25 19:37:48 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fun_error(t_minishell *mini, int i, char *str)
{
	if (i == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		ft_exit(NULL, 1, mini);
	}
}

static void	is_directory(char *path, t_minishell *mini)
{
	struct stat	path_stat;

	if (stat(path, &path_stat))
	{
		perror("minishell: stat");
		ft_exit(NULL, 1, mini);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_exit(": is a directory", 126, mini);
	}
	if (access(path, F_OK | X_OK) == -1)
		catch_error(mini, 126, path);
}

void	process_code(t_exec *tree, t_minishell *mini)
{
	char	*path;
	char	**cmd;

	open_files(mini, tree);
	if (tree->fdin != 0)
	{
		fun_error(mini, dup2(tree->fdin, 0), "dup2");
		fun_error(mini, close(tree->fdin), "close");
	}
	if (tree->fdout != 1)
	{
		fun_error(mini, dup2(tree->fdout, 1), "dup2");
		fun_error(mini, close(tree->fdout), "close");
	}
	close_sibling_fd(mini->tree);
	if (tree->tokens && tree->tokens->token[0])
	{
		path = ft_get_path(mini, tree->tokens);
		if (!path)
			catch_error(mini, 127, tree->tokens->token);
		is_directory(path, mini);
	}
	cmd = to_array(tree->tokens, mini);
	catch_error(mini, execve(path, cmd, mini->env), tree->tokens->token);
	ft_exit(NULL, 1, mini);
}

int	run_command(t_exec *tree, t_minishell *mini)
{
	pid_t	pid;

	if (!mini)
		return (0);
	signals_handle(mini, tree);
	pid = fork();
	fun_error(mini, pid, "fork");
	if (pid == 0 && mini && tree)
		process_code(tree, mini);
	else
	{
		if (tree->fdin != 0)
			fun_error(mini, close(tree->fdin), "close");
		if (tree->fdout != 1)
			fun_error(mini, close(tree->fdout), "close");
	}
	return (pid);
}
