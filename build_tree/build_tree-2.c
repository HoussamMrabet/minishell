/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree-2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:59:57 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 08:00:58 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token_tree(t_tokenizer **tokens, t_tokenizer *new)
{
	t_tokenizer	*tmp;

	tmp = *tokens;
	if (!tmp)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->next = NULL;
	}
}

static t_bool	is_last(t_tokenizer *token, t_type type1, unsigned int lvl)
{
	t_tokenizer	*tokens;
	t_type		type2;

	if (type1 == AND)
		type2 = OR;
	else
		type2 = PIPE;
	tokens = token->next;
	while (tokens)
	{
		if ((tokens->type == type1 || tokens->type == type2)
			&& tokens->lvl == lvl)
			return (FALSE);
		tokens = tokens->next;
	}
	return (TRUE);
}

void	split_tree_tokens(t_minishell *mini, t_exec **tree
	, t_type type, unsigned int current_lvl)
{
	t_tokenizer	*token;
	t_type		type2;

	(type == AND) && (type2 = OR);
	(type == PIPE) && (type2 = PIPE);
	token = (*tree)->tokens;
	while (token && !((token->type == type || token->type == type2)
			&& is_last(token, type, current_lvl)))
	{
		add_token_tree(&((*tree)->left->tokens), token_dup(mini, token));
		(*tree)->left->type = CMD;
		1 && ((*tree)->left->is_pipe = (type == PIPE), token = token->next);
	}
	(*tree)->tokens = token_dup(mini, token);
	(*tree)->type = token->type;
	1 && ((*tree)->left->is_pipe = (type == PIPE), token = token->next);
	while (token)
	{
		add_token_tree(&((*tree)->right->tokens), token_dup(mini, token));
		(*tree)->right->type = CMD;
		1 && ((*tree)->right->is_pipe = (type == PIPE), token = token->next);
	}
	(*tree)->iofiles = NULL;
	build_tree(mini, &(*tree)->left, current_lvl);
	build_tree(mini, &(*tree)->right, current_lvl);
}
