/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:46:12 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/29 18:51:21 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_flag(char *token)
{
	int	i;

	if (token[0] != '-')
		return (FALSE);
	i = 1;
	if (!token[i])
		return (FALSE);
	while (token[i])
	{
		if (token[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_echo(t_minishell *m, t_exec *tree)
{
	char		*res;
	t_tokenizer	*token;
	t_bool		with_op;

	if (open_files_builtin(tree))
		return ;
	token = tree->tokens->next;
	(1) && (with_op = FALSE, res = ft_strdup("", m, &m->local));
	(token && token->type == SPACES) && (token = token->next);
	if (token && (!ft_strcmp("-n", token->token) || is_flag(token->token)))
		(1) && (with_op = TRUE, token = token->next);
	while (token && (token->type == SPACES
			|| !ft_strcmp("-n", token->token) || is_flag(token->token)))
		token = token->next;
	while (token)
	{
		if (token->type == SPACES && token->next)
			res = ft_strjoin(res, " ", m, &m->local);
		else if (token->type != SPACES)
			res = ft_strjoin(res, token->token, m, &m->local);
		token = token->next;
	}
	(!with_op) && (res = ft_strjoin(res, "\n", m, &m->local));
	ft_putstr_fd(res, tree->fdout);
	exit_status(0, TRUE);
}
