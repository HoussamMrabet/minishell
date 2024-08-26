/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:35:15 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/26 06:59:36 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(t_minishell *minishell, char **tokens, char sign)
{
	int			i;
	int			j;
	char		*tmp;
	char		*value;

	(1) && (i = 0, value = ft_strdup("", minishell, &minishell->local));
	while ((*tokens)[++i] != sign)
	{
		j = 0;
		while (((*tokens) + i)[j] != sign)
			j++;
		tmp = ft_substr(minishell, (*tokens) + i, 0, j);
		value = ft_strjoin(value, tmp, minishell, &minishell->local);
		i += j - 1;
	}
	*tokens = value;
}

void	merge_tokens(t_minishell *minishell, t_tokenizer **tokens)
{
	t_tokenizer	*t;

	t = *tokens;
	while (t)
	{
		if (t->next && (t->type == TEXT || t->type == WILD_CARD
				|| t->type == S_QUOTE || t->type == D_QUOTE))
		{
			if (t->next->type == S_QUOTE || t->next->type == WILD_CARD
				|| t->next->type == D_QUOTE || t->next->type == TEXT)
			{
				t->token = ft_strjoin(t->token,
						t->next->token, minishell, &minishell->local);
				if (t->next->type == WILD_CARD)
					t->type = WILD_CARD;
				if (t->next->amb)
					t->amb = TRUE;
				t->next = t->next->next;
				continue ;
			}
		}
		t = t->next;
	}
}

void	split_commands(t_minishell *m, t_tokenizer **tokens)
{
	t_tokenizer	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		(tmp->type == DEL && tmp->next) && (tmp->next->type = DELIM);
		if (tmp->type == TEXT || tmp->type == D_QUOTE
			|| tmp->type == S_QUOTE)
			tmp->type = CMD;
		tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == CMD && tmp->next && tmp->next->type == CMD)
		{
			tmp->token = ft_strjoin(tmp->token, "\n", m, &m->local);
			tmp->token = ft_strjoin(tmp->token, tmp->next->token, m, &m->local);
			tmp->next = tmp->next->next;
			continue ;
		}
		tmp = tmp->next;
	}
}

void	separate_wildcards(t_tokenizer **tokens)
{
	t_tokenizer	*token;

	token = *tokens;
	while (token)
	{
		if (token->type == TEXT && ft_strchr(token->token, '*'))
			token->type = WILD_CARD;
		token = token->next;
	}
}
