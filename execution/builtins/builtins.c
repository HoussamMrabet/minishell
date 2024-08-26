/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:11:51 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 12:00:51 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	built_in_exec(t_minishell *minishell, t_exec *tree)
{
	t_tokenizer	*token;

	token = tree->tokens;
	(token && token->type == SPACES) && (token = token->next);
	if (!token || token->type == SPACES)
		return (1);
	if (token && !ft_strcmp(token->token, "env"))
		return (ft_env(minishell, tree), 0);
	else if (token && !ft_strcmp(token->token, "echo"))
		return (ft_echo(minishell, tree), 0);
	else if (token && !ft_strcmp(token->token, "pwd"))
		return (exit_status(0, TRUE), ft_pwd(minishell, tree), 0);
	else if (token && !ft_strcmp(token->token, "export"))
	{
		exit_status(0, TRUE);
		return (ft_export(minishell, tree), 0);
	}
	else if (token && !ft_strcmp(token->token, "unset"))
		return (ft_unset(minishell, tree), 0);
	else if (token && !ft_strcmp(token->token, "cd"))
		return (exit_status(0, TRUE), ft_cd(minishell, tree), 0);
	else if (token && !ft_strcmp(token->token, "exit"))
		return (ft_exit_builtin(minishell, tree), 0);
	return (1);
}

int	check_builtins(t_minishell *minishell, t_exec *tree)
{
	int	res;

	res = built_in_exec(minishell, tree);
	if (tree->fdin != 0 && res == 0)
		close(tree->fdin);
	if (tree->fdout != 1 && res == 0)
		close(tree->fdout);
	return (res);
}
