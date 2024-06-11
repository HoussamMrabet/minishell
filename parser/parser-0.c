/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 06:41:00 by hmrabet           #+#    #+#             */
/*   Updated: 2024/06/11 09:07:43 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(t_minishell *minishell, char **tokens, char sign)
{
	int			i;
	int			j;
	char		*tmp;
	char		*value;

	(1) && (i = 0, value = ft_strdup("", &minishell->local));
	(!value) && (j = ft_exit("Allocation error", 1, minishell));
	while ((*tokens)[++i] != sign)
	{
		j = 0;
		while (((*tokens) + i)[j] != sign)
			j++;
		tmp = ft_substr(&minishell->local, (*tokens) + i, 0, j);
		value = ft_strjoin(value, tmp, &minishell->local);
		(!value) && (ft_exit("Allocation error", 1, minishell));
		i += j - 1;
	}
	*tokens = value;
}

// static void	merge_tokens(t_minishell *minishell, t_tokenizer **tokens)
// {
// 	t_tokenizer	*t;

// 	t = *tokens;
// 	while (t)
// 	{
// 		if (t->next && (t->type == TEXT || t->type == WILD_CARD
// 				|| t->type == S_QUOTE || t->type == D_QUOTE))
// 		{
// 			if (t->next->type == S_QUOTE || t->next->type == WILD_CARD
// 				|| t->next->type == D_QUOTE || t->next->type == TEXT)
// 			{
// 				t->token = ft_strjoin(t->token,
// 						t->next->token, &minishell->local);
// 				if (!t->token)
// 					ft_exit("Allocation error", 1, minishell);
// 				if (t->next->type == WILD_CARD)
// 					t->type = WILD_CARD;
// 				t->next = t->next->next;
// 				continue ;
// 			}
// 		}
// 		if (t->next && t->next->type == SPACES)
// 			t->next = t->next->next;
// 		t = t->next;
// 	}
// }

// static void	split_commands(t_minishell *m, t_tokenizer **tokens)
// {
// 	t_tokenizer	*tmp;

// 	tmp = *tokens;
// 	while (tmp)
// 	{
// 		(tmp->type == DELIMITER && tmp->next) && (tmp->next->type = DELIM);
// 		if (tmp->type == TEXT || tmp->type == D_QUOTE
// 			|| tmp->type == S_QUOTE)
// 			tmp->type = CMD;
// 		tmp = tmp->next;
// 	}
// 	tmp = *tokens;
// 	while (tmp)
// 	{
// 		if (tmp->type == CMD && tmp->next && tmp->next->type == CMD)
// 		{
// 			tmp->token = ft_strjoin(tmp->token, "\n", &m->local);
// 			(!tmp->token) && (m->lvl = ft_exit("Allocation error", 1, m));
// 			tmp->token = ft_strjoin(tmp->token, tmp->next->token, &m->local);
// 			(!tmp->token) && (m->lvl = ft_exit("Allocation error", 1, m));
// 			tmp->next = tmp->next->next;
// 			continue ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

static void	separate_wildcards(t_tokenizer **tokens)
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

void	parser(t_minishell *minishell)
{
	int			i;
	t_tokenizer	*tokens;

	i = 0;
	tokens = minishell->tokens;
	// replace_expand_values(minishell, &tokens);
	separate_wildcards(&tokens);
	// merge_tokens(minishell, &tokens);
	// split_commands(minishell, &tokens);
	// ft_wildcards(minishell);
	// merge_wildcards(minishell);
}
