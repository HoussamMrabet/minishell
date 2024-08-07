/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 06:41:00 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/16 12:24:17 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_tokens_level(t_tokenizer **tokens)
{
	t_tokenizer		*token;
	t_tokenizer		*tmp;
	unsigned int	level;

	(1) && (level = 0, token = *tokens);
	while (token)
	{
		if (token->type == PAR)
		{
			(token->token[0] == '(') && (level++);
			(token->token[0] == ')') && (level--);
		}
		(1) && (token->lvl = level, token = token->next);
	}
	while ((*tokens)->type == PAR)
		*tokens = (*tokens)->next;
	token = *tokens;
	while (token)
	{
		tmp = token->next;
		while (tmp && !(tmp->type != PAR))
			tmp = tmp->next;
		(1) && (token->next = tmp, token = token->next);
	}
}

static t_bool	check_signs(t_tokenizer *tokens, t_type type)
{
	t_tokenizer	*token;

	token = tokens;
	while (token)
	{
		if (token->type == type)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

static void	update_tokens2(t_tokenizer *tmp, t_tokenizer *t)
{
	t_tokenizer	*t2;

	t->next = tmp->next;
	t2 = tmp;
	while (t2->next && (t2->next->type == IN_RED
			|| t2->next->type == OUT_RED
			|| t2->next->type == APPEND || t2->next->type == DEL))
	{
		t2 = t2->next;
		if (t2->next && t2->next->type == SPACES)
			t2 = t2->next;
		while (t2->next && (t2->next->type == TEXT || t2->next->type == D_QUOTE
				|| t2->next->type == S_QUOTE || t2->next->type == WILD_CARD
				|| t2->next->type == DELIM || t2->next->type == Q_DELIM))
			t2 = t2->next;
		if (t2->next && t2->next->type == SPACES)
			t2 = t2->next;
	}
	tmp->next = t2->next;
	t2->next = tmp;
}

static void	update_tokens(t_minishell *minishell)
{
	t_tokenizer	*t;
	t_tokenizer	*tmp;

	merge_delimiters(minishell, &minishell->tokens);
	t = minishell->tokens;
	while (t)
	{
		if ((t)->next && (t)->next->type == PAR && (t)->next->token[0] == ')')
		{
			tmp = (t)->next;
			if (tmp->next && tmp->next->type == SPACES)
				tmp->next = tmp->next->next;
			if (tmp->next && (tmp->next->type == IN_RED
					|| tmp->next->type == OUT_RED
					|| tmp->next->type == APPEND || tmp->next->type == DEL))
				update_tokens2(tmp, t);
		}
		(t) = (t)->next;
	}
}

void	parser(t_minishell *minishell)
{
	int			i;
	t_tokenizer	*token;
	t_exec		*tree;

	i = 0;
	update_tokens(minishell);
	token = minishell->tokens;
	set_tokens_level(&token);
	here_doc(minishell);
	minishell->tree = ft_malloc(minishell, &minishell->local, sizeof(t_exec));
	tree = minishell->tree;
	tree->tokens = token;
	tree->type = CMD;
	tree->fdin = 0;
	tree->fdout = 1;
	tree->iofiles = NULL;
	tree->left = NULL;
	tree->right = NULL;
	if (check_signs(token, AND) || check_signs(token, OR)
		|| check_signs(token, PIPE))
		build_tree(minishell, &tree, 0);
}
