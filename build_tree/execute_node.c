/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:49:10 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/29 13:55:28 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_items(t_minishell *m, t_tokenizer **tokens)
{
	t_tokenizer	*o;
	t_tokenizer	*token;
	t_tokenizer	*new;
	char		**items;
	int			i;

	items = ft_split_local((*tokens)->token, '\002', m);
	(1) && (token = (*tokens)->next, o = *tokens, i = -1);
	while (items && items[++i])
	{
		if (i == 0)
			(*tokens)->token = ft_strdup(items[i], m, &m->local);
		else
		{
			new = ft_malloc(m, &m->local, sizeof(t_tokenizer));
			(1) && (new->amb = o->amb, new->type = SPACES, new->lvl = o->lvl);
			new->token = ft_strdup(" ", m, &m->local);
			(1) && (new->next = token, (*tokens)->next = new, *tokens = new);
			new = ft_malloc(m, &m->local, sizeof(t_tokenizer));
			(1) && (new->amb = o->amb, new->type = o->type, new->lvl = o->lvl);
			(1) && (new->chain = i, new->is_expand = (*tokens)->is_expand);
			new->token = ft_strdup(items[i], m, &m->local);
			(1) && (new->next = token, (*tokens)->next = new, *tokens = new);
		}
	}
}

static void	split_expands(t_minishell *m, t_tokenizer **t)
{
	t_tokenizer	*token;
	t_bool		sbool;

	token = *t;
	sbool = FALSE;
	while (token)
	{
		if (token->type == TEXT && token->amb == FALSE)
			split_items(m, &token);
		token = token->next;
	}
}

static void	remove_empty(t_minishell *m, t_exec **node, t_tokenizer **tokens)
{
	t_tokenizer	*token;

	while (*tokens)
	{
		if ((*tokens)->type == TEXT
			&& !ft_strtrim(m, (*tokens)->token, "	 \002")[0])
		{
			*tokens = (*tokens)->next;
			(*node)->tokens = *tokens;
		}
		else
			break ;
	}
	token = *tokens;
	while (token)
	{
		if (token->next && token->next->type == TEXT && !token->next->token[0])
			token->next = token->next->next;
		else
			token = token->next;
	}
}

void	prepare_node_for_execute(t_minishell *minishell, t_exec *node)
{
	t_tokenizer	*tokens;

	tokens = node->tokens;
	if (tokens && tokens->type == SPACES)
		node->tokens = tokens->next;
	minishell->is_empty = FALSE;
	tokens = node->tokens;
	if (tokens && !ft_strtrim(minishell, tokens->token, " \t|&")[0])
		minishell->is_empty = TRUE;
	replace_expand_values(minishell, &tokens);
	check_ambiguous(minishell, &tokens);
	split_expands(minishell, &tokens);
	remove_empty(minishell, &node, &tokens);
	separate_wildcards(&tokens);
	merge_tokens(minishell, &tokens);
	split_commands(minishell, &tokens);
	ft_wildcards(minishell, &tokens);
	merge_wildcards(minishell, &tokens);
	set_io_tokens(minishell, &node);
	set_loadash(minishell, node);
}
