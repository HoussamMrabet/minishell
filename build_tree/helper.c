/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 08:51:08 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 17:06:38 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_loadash(t_minishell *minishell, t_exec *node)
{
	t_tokenizer	*token;
	char		*_loadash;

	_loadash = ft_strdup("", minishell, &minishell->local);
	token = node->tokens;
	while (token)
	{
		if (token->token[0])
			_loadash = ft_strdup(token->token, minishell, &minishell->local);
		token = token->next;
	}
	if (_loadash[0])
	{
		minishell->_ = ft_strdup(_loadash, minishell, &minishell->global);
		set_fake_env_value(minishell, "_", "/usr/bin/env");
		set_env_value(minishell, "_", "/usr/bin/env");
	}
}

static void	ambiguous_left(t_minishell *minishell, t_tokenizer **token)
{
	while (!(*token)->amb && (*token)->next && ((*token)->next->type == TEXT
			|| (*token)->next->type == S_QUOTE
			|| (*token)->next->type == D_QUOTE))
		*token = (*token)->next;
	if ((*token)->amb && !ft_strchr(ft_strtrim(minishell, (*token)->token,
				"	 \002"), '\002') && (*token)->token[0] != '\002')
	{
		(*token)->token = ft_strtrim(minishell, (*token)->token, "	 \002");
		(*token)->amb = FALSE;
	}
}

static void	ambiguous_right(t_minishell *minishell, t_tokenizer **t)
{
	if ((*t)->amb && (*t)->next && ((*t)->next->type == TEXT
			|| (*t)->next->type == S_QUOTE || (*t)->next->type == D_QUOTE))
	{
		if (!ft_strchr(ft_strtrim(minishell, (*t)->token, "	 \002"), '\002')
			&& (*t)->token[0]
			&& (*t)->token[ft_strlen((*t)->token) - 1] != '\002')
		{
			(*t)->token = ft_strtrim(minishell, (*t)->token, "	 \002");
			(*t)->amb = FALSE;
		}
	}
	else if (!(*t)->amb)
		ambiguous_left(minishell, t);
}

void	check_ambiguous(t_minishell *minishell, t_tokenizer **tokens)
{
	t_tokenizer	*t;

	t = *tokens;
	while (t)
	{
		if (t->type == OUT_RED || t->type == IN_RED || t->type == APPEND)
		{
			(1) && (t = t->next, (t->type == SPACES) && (t = t->next));
			if (t->amb && (!t->next || (t->next && t->next->type != TEXT
						&& t->next->type != S_QUOTE
						&& t->next->type != D_QUOTE)))
			{
				if (!ft_strchr(ft_strtrim(minishell, t->token, "	 \002"),
						'\002'))
					1 && (t->token = ft_strtrim(minishell, t->token, "	 \002")
						, t->amb = FALSE);
			}
			else
				ambiguous_right(minishell, &t);
		}
		else
			t->amb = FALSE;
		t = t->next;
	}
}
