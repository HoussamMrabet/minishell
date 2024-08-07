/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:27:10 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/15 15:13:01 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_text_expand2(t_minishell *m, char **tok, char **val, int *i)
{
	int		j;
	char	*tmp;
	char	*str;

	if ((*tok)[(*i) + 1] == '?')
		(1) && (str = ft_itoa(m, &m->local, exit_status(0, FALSE)),
			*val = ft_strjoin((*val), str, m, &m->local), (*i)++);
	else if ((*tok)[(*i) + 1] == '_')
		(1) && (*val = ft_strjoin((*val), m->_, m, &m->local), (*i)++);
	else if (!(*tok)[(*i) + 1] || !ft_isalnum((*tok)[(*i) + 1]))
		(*val) = ft_strjoin((*val), "$", m, &m->local);
	else
	{
		j = 1;
		if ((*tok + (*i))[j] == '_' || ft_isal((*tok + (*i))[j]))
		{
			j++;
			while ((*tok + (*i))[j] == '_' || ft_isalnum((*tok + (*i))[j]))
				j++;
		}
		(1) && (j--, str = ft_substr(m, ((*tok + (*i)) + 1), 0, j));
		tmp = get_env_value(m, str);
		(!tmp) && (tmp = ft_strdup("", m, &m->local));
		(1) && (*val = ft_strjoin((*val), tmp, m, &m->local), (*i) += j);
	}
}

void	handle_text_expand(t_minishell *m, t_tokenizer *tok, char **tokens)
{
	int			i;
	int			j;
	char		*tmp;
	char		*val;

	(1) && (i = 0, val = ft_strdup("", m, &m->local));
	while ((*tokens)[i])
	{
		if ((*tokens)[i] == '$')
		{
			handle_text_expand2(m, tokens, &val, &i);
			if (tok && ft_strchr(val, ' '))
				tok->ambiguous = TRUE;
		}
		else
		{
			j = 0;
			while ((*tokens + i)[j] && (*tokens + i)[j] != '$')
				j++;
			tmp = ft_substr(m, (*tokens) + i, 0, j);
			(1) && (val = ft_strjoin(val, tmp, m, &m->local), i += j - 1);
		}
		i++;
	}
	*tokens = val;
}

static void	handle_quote_expand2(t_minishell *m, char **tok, char **val, int *i)
{
	int		j;
	char	*tmp;
	char	*str;

	if ((*tok)[(*i) + 1] == '?')
		(1) && (str = ft_itoa(m, &m->local, exit_status(0, FALSE)),
			*val = ft_strjoin((*val), str, m, &m->local), (*i)++);
	else if ((*tok)[(*i) + 1] == '_')
		(1) && (*val = ft_strjoin((*val), m->_, m, &m->local), (*i)++);
	else if ((*tok)[(*i) + 1] == '"' || !ft_isalnum((*tok)[(*i) + 1]))
		(*val) = ft_strjoin((*val), "$", m, &m->local);
	else
	{
		j = 1;
		if ((*tok + (*i))[j] == '_' || ft_isal((*tok + (*i))[j]))
		{
			j++;
			while ((*tok + (*i))[j] == '_' || ft_isalnum((*tok + (*i))[j]))
				j++;
		}
		(1) && (j--, str = ft_substr(m, ((*tok + (*i)) + 1), 0, j));
		tmp = get_env_value(m, str);
		(!tmp) && (tmp = ft_strdup("", m, &m->local));
		(1) && (*val = ft_strjoin((*val), tmp, m, &m->local), (*i) += j);
	}
}

static void	handle_quote_expand(t_minishell *minishell, char **tokens)
{
	int			i;
	int			j;
	char		*tmp;
	char		*value;

	(1) && (i = 0, value = ft_strdup("", minishell, &minishell->local));
	while ((*tokens)[++i] != '"')
	{
		if ((*tokens)[i] == '$')
			handle_quote_expand2(minishell, tokens, &value, &i);
		else
		{
			j = 0;
			while (((*tokens) + i)[j] != '"' && ((*tokens) + i)[j] != '$')
				j++;
			tmp = ft_substr(minishell, (*tokens) + i, 0, j);
			value = ft_strjoin(value, tmp, minishell, &minishell->local);
			i += j - 1;
		}
	}
	*tokens = value;
}

void	replace_expand_values(t_minishell *minishell, t_tokenizer **tokens)
{
	t_tokenizer	*token;

	token = *tokens;
	while (token)
	{
		if (token->type == TEXT)
			handle_text_expand(minishell, token, &token->token);
		else if (token->type == D_QUOTE)
			handle_quote_expand(minishell, &token->token);
		else if (token->type == S_QUOTE)
			remove_quotes(minishell, &token->token, '\'');
		token = token->next;
	}
}
