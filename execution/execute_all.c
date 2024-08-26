/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:44:04 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/08/25 12:02:06 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(pid_t pid)
{
	int	status;
	int	res;

	res = 0;
	if (waitpid(pid, &status, WUNTRACED | WCONTINUED) > -1)
	{
		if (WEXITSTATUS(status))
			res = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			res = 128 + WTERMSIG(status);
	}
	exit_status(res, 1);
}

void	execute_pipes(t_exec *tree, t_minishell *mini)
{
	t_pids_list	*pids;

	pids = NULL;
	execute_one(tree, mini, &pids);
	while (pids)
	{
		wait_all(pids->pid);
		pids = pids->next;
	}
	while (1)
	{
		if (waitpid(-1, NULL, 0) == -1)
			break ;
	}
}

void	execute_one(t_exec *tree, t_minishell *mini, t_pids_list **pids)
{
	if (tree->type == CMD)
	{
		exit_status(0, tree->is_pipe);
		prepare_node_for_execute(mini, tree);
		if (check_builtins(mini, tree))
		{
			if (!create_one_pid(mini, pids, (pid_t)run_command(tree, mini)))
				ft_exit("minishell: Allocation error", 1, mini);
		}
		else
			*pids = NULL;
	}
	if (tree->type == PIPE)
	{
		execute_one(tree->left, mini, pids);
		execute_one(tree->right, mini, pids);
	}
}

t_pids_list	*create_one_pid(t_minishell *mini, t_pids_list **pids, pid_t pid)
{
	t_pids_list	*new;
	t_pids_list	*tmp;

	new = (t_pids_list *)ft_malloc(mini, &mini->local, sizeof(t_pids_list));
	if (!new)
		return (NULL);
	new->pid = pid;
	new->next = NULL;
	if (!*pids)
		*pids = new;
	else
	{
		tmp = *pids;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

int	execute_all(t_exec *tree, t_minishell *mini)
{
	if (!tree || !tree->tokens)
		return (0);
	if (tree->type == OR)
	{
		execute_all(tree->left, mini);
		if (exit_status(0, 0) != 0)
			execute_all(tree->right, mini);
	}
	if (tree->type == AND)
	{
		execute_all(tree->left, mini);
		if (exit_status(0, 0) == 0)
			execute_all(tree->right, mini);
	}
	if (tree->type == PIPE || tree->type == CMD)
		execute_pipes(tree, mini);
	return (0);
}
