/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:46:12 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 16:47:52 by mel-hamd         ###   ########.fr       */
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

	open_files(m, tree);
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
		if (!(!res[0] && token->type == SPACES))
			res = ft_strjoin(res, token->token, m, &m->local);
		token = token->next;
	}
	(!with_op) && (res = ft_strjoin(res, "\n", m, &m->local));
	ft_putstr_fd(res, tree->fdout);
	exit_status(0, TRUE);
}
