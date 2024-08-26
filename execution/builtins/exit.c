/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:03:36 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/26 17:47:44 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	too_many_arguments(t_tokenizer *tokens)
{
	t_tokenizer	*token;

	token = tokens->next;
	if (!token)
		return (FALSE);
	if (token->type == SPACES)
		token = token->next;
	if (token)
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	ft_isnum(char *s)
{
	int	i;

	i = 0;
	if (s[i] && (s[i] == '-' || s[i] == '+'))
		i++;
	if (!s[i])
		return (FALSE);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	ft_num_required(t_minishell *mini, char *token, t_exec *tree)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	if (!tree->is_pipe)
		ft_exit(NULL, 255, mini);
	else
		exit_status(255, TRUE);
	return (1);
}

static int	ft_exit_builtin2(t_minishell *m, t_exec *tree, t_tokenizer **tok)
{
	if (!ft_isnum(ft_strtrim(m, (*tok)->token, " ")))
	{
		if (ft_num_required(m, (*tok)->token, tree))
			return (1);
	}
	else if (too_many_arguments((*tok)))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit_status(1, TRUE);
		return (1);
	}
	// else if (ft_strlen(ft_strtrim(m, (*tok)->token, " ")) >= 21
	// 	|| ft_atoul((*tok)->token) > LLONG_MAX)
	// {
	// 	if (ft_num_required(m, (*tok)->token, tree))
	// 		return (1);
	// }
	return (0);
}

void	ft_exit_builtin(t_minishell *m, t_exec *tree)
{
	t_tokenizer		*tok;

	if (open_files_builtin(tree))
		return ;
	if (!tree->is_pipe)
		ft_putstr_fd("exit\n", tree->fdout);
	tok = tree->tokens->next;
	(tok && tok->type == SPACES) && (tok = tok->next);
	if (!tok)
	{
		if (!tree->is_pipe)
			ft_exit(NULL, exit_status(0, FALSE), m);
		else
			exit_status(0, TRUE);
	}
	else
	{
		if (ft_exit_builtin2(m, tree, &tok))
			return ;
	}
	tok && (exit_status(ft_atoi(ft_strtrim(m, tok->token, " ")), TRUE));
	if (!tree->is_pipe)
		ft_exit(NULL, exit_status(0, FALSE), m);
}
