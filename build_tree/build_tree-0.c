/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree-0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:05:18 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/07/08 13:25:34 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_signs(t_tokenizer *tok, t_type type, unsigned int level)
{
	t_tokenizer	*token;

	token = tok;
	while (token)
	{
		if (token->type == type && token->lvl == level)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

static unsigned int	get_highest_lvl(t_tokenizer *tokens)
{
	t_tokenizer		*token;
	unsigned int	highest_lvl;

	highest_lvl = tokens->lvl;
	token = tokens;
	while (token)
	{
		if (token->lvl > highest_lvl)
			highest_lvl = token->lvl;
		token = token->next;
	}
	return (highest_lvl);
}

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

static void	split_tree_tokens(t_minishell *mini, t_exec **tree
	, t_type type, unsigned int current_lvl)
{
	t_tokenizer	*token;

	token = (*tree)->tokens;
	while (token && !(token->type == type && token->lvl == current_lvl))
	{
		add_token_tree(&((*tree)->left->tokens), token_dup(mini, token));
		(*tree)->left->type = CMD;
		token = token->next;
	}
	(*tree)->tokens = token_dup(mini, token);
	(*tree)->type = type;
	token = token->next;
	while (token)
	{
		add_token_tree(&((*tree)->right->tokens), token_dup(mini, token));
		(*tree)->right->type = CMD;
		token = token->next;
	}
	(*tree)->iofiles = NULL;
	build_tree(mini, &(*tree)->left, current_lvl);
	build_tree(mini, &(*tree)->right, current_lvl);
}

void	build_tree(t_minishell *mini, t_exec **tree, unsigned int current_lvl)
{
	unsigned int	max_lvl;

	(*tree)->left = ft_malloc(mini, &mini->local, sizeof(t_exec));
	(*tree)->right = ft_malloc(mini, &mini->local, sizeof(t_exec));
	(*tree)->left->tokens = NULL;
	(*tree)->right->tokens = NULL;
	(1) && ((*tree)->fdin = 0, (*tree)->fdout = 1, (*tree)->iofiles = NULL);
	max_lvl = get_highest_lvl((*tree)->tokens);
	if (current_lvl <= max_lvl)
	{
		if (check_signs((*tree)->tokens, AND, current_lvl))
			split_tree_tokens(mini, tree, AND, current_lvl);
		else if (check_signs((*tree)->tokens, OR, current_lvl))
			split_tree_tokens(mini, tree, OR, current_lvl);
		else if (check_signs((*tree)->tokens, PIPE, current_lvl))
			split_tree_tokens(mini, tree, PIPE, current_lvl);
		else
			build_tree(mini, tree, current_lvl + 1);
	}
	else
	{
		(1) && ((*tree)->left = NULL, (*tree)->right = NULL
				, (*tree)->iofiles = NULL);
		return ;
	}
}
