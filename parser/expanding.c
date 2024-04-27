/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:27:10 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/27 12:10:39 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_text_expand2(t_minishell *m, char **tok, char **val, int *i)
{
	int		j;
	char	*tmp;

	if (!(*tok)[(*i) + 1])
		(*val) = ft_strjoin((*val), "$", &m->local);
	else if ((*tok)[(*i) + 1] == '$')
		(1) && ((*val) = ft_strjoin((*val),
			ft_itoa(&m->local, getpid()), &m->local), (*i)++);
	else if ((*tok)[(*i) + 1] == '?')
		(1) && ((*val) = ft_strjoin((*val), ft_itoa(&m->local,
			exit_status(0, FALSE)), &m->local), (*i)++);
	else
	{
		j = 1;
		while (ft_isalnum((*tok + (*i))[j]))
			j++;
		(1) && (j--, tmp = get_env_value(m,
			ft_substr(&m->local, ((*tok + (*i)) + 1), 0, j), FALSE));
		if (!tmp)
			tmp = ft_strdup("", &m->local);
		(1) && ((*val) = ft_strjoin((*val), tmp, &m->local), (*i) += j);
	}
}

static void	handle_text_expand(t_minishell *minishell, char **tokens)
{
	int			i;
	int			j;
	char		*tmp;
	char		*val;

	(1) && (i = 0, val = ft_strdup("", &minishell->local));
	while ((*tokens)[i])
	{
		if ((*tokens)[i] == '$')
			handle_text_expand2(minishell, tokens, &val, &i);
		else
		{
			j = 0;
			while ((*tokens + i)[j] && (*tokens + i)[j] != '$')
				j++;
			tmp = ft_substr(&minishell->local, (*tokens) + i, 0, j);
			val = ft_strjoin(val, tmp, &minishell->local);
			i += j - 1;
		}
		i++;
	}
	*tokens = val;
}

static void	handle_quote_expand2(t_minishell *m, char **tok, char **val, int *i)
{
	int		j;
	char	*tmp;

	if ((*tok)[(*i) + 1] == '"')
		(*val) = ft_strjoin((*val), "$", &m->local);
	else if ((*tok)[(*i) + 1] == '$')
		(1) && ((*val) = ft_strjoin((*val),
			ft_itoa(&m->local, getpid()), &m->local), (*i)++);
	// else if ((*tok)[(*i) + 1] == '?')
	// 	(1) && ((*val) = ft_strjoin((*val), ft_itoa(&m->local,
	// 		exit_status(0, FALSE)), &m->local), (*i)++);
	else
	{
		j = 1;
		while (ft_isalnum((*tok + (*i))[j]))
			j++;
		(1) && (j--, tmp = get_env_value(m,
			ft_substr(&m->local, (*tok) + ((*i) + 1), 0, j), FALSE));
		if (!tmp)
			tmp = ft_strdup("", &m->local);
		(*val) = ft_strjoin((*val), tmp, &m->local);
		*i += j;
	}
}

static void	handle_quote_expand(t_minishell *minishell, char **tokens)
{
	int			i;
	int			j;
	char		*tmp;
	char		*value;

	(1) && (i = 0, value = ft_strdup("", &minishell->local));
	while ((*tokens)[++i] != '"')
	{
		if ((*tokens)[i] == '$')
			handle_quote_expand2(minishell, tokens, &value, &i);
		else
		{
			j = 0;
			while (((*tokens) + i)[j] != '"' && ((*tokens) + i)[j] != '$')
				j++;
			tmp = ft_substr(&minishell->local, (*tokens) + i, 0, j);
			value = ft_strjoin(value, tmp, &minishell->local);
			i += j - 1;
		}
	}
	*tokens = value;
}

void	replace_expand_values(t_minishell *minishell, t_tokenizer **tokens)
{
	t_tokenizer	*token;
	t_bool		is_del;

	is_del = FALSE;
	token = *tokens;
	while (token)
	{
		if (token->type == DELIMITER)
			is_del = TRUE;
		else if (token->type == TEXT && !is_del)
			handle_text_expand(minishell, &token->token);
		else if (token->type == D_QUOTE && !is_del)
			handle_quote_expand(minishell, &token->token);
		else if (token->type == D_QUOTE)
			remove_quotes(minishell, &token->token, '"');
		else if (token->type == S_QUOTE)
			remove_quotes(minishell, &token->token, '\'');
		if (token->type != SPACES && token->type != DELIMITER && token->next
			&& token->next->type == SPACES)
			is_del = FALSE;
		token = token->next;
	}
}
