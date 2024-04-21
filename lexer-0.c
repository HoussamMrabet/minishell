/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:31:22 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/21 17:39:37 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokenizer **tokens)
{
	t_tokenizer	*to_free;
	t_tokenizer	*to_hold;

	to_free = *tokens;
	while (to_free)
	{
		to_hold = to_free->next;
		free(to_free->token);
		free(to_free);
		to_free = to_hold;
	}
}

void	add_token(t_tokenizer **tokens, t_tokenizer *new)
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
	}
}

void	handle_double_quotes(t_minishell *m, t_tokenizer **t, char *s, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 1, k = 0, new = malloc(sizeof(t_tokenizer)));
	if (!new)
	{
		free_tokens(t);
		ft_exit("Allocation error", 1, &m->garbage);
	}
	while (s[*i + j] && s[*i + j] != '"')
		j++;
	if (s[*i + j] == '"')
		j++;
	(1) && (new->token = malloc(j + 1), new->type = D_QUOTE, new->next = NULL);
	if (!new->token)
	{
		free(new);
		free_tokens(t);
		ft_exit("Allocation error", 1, &m->garbage);
	}
	while (k < j)
		(1) && (new->token[k] = s[*i], k++, (*i)++);
	(1) && ((*i)--, new->token[k] = '\0');
	add_token(t, new);
}

void	lexer(t_minishell *minishell, char *input)
{
	int			i;
	t_tokenizer	*tokens;
	t_tokenizer	*tmp;

	i = 0;
	tokens = NULL;
	minishell->tokens = tokens;
	while (input[i])
	{
		if (input[i] == '\'')
			handle_single_quotes(minishell, &tokens, input, &i);
		else if (input[i] == '"')
			handle_double_quotes(minishell, &tokens, input, &i);
		else if (input[i] == '<' || input[i] == '>')
			handle_red_and_del(minishell, &tokens, input, &i);
		else if (input[i] == '|')
			handle_pipe_or_sign(minishell, &tokens, input, &i);
		else if (input[i] == '&' && input[i + 1] == '&')
			handle_and_sign(minishell, &tokens, input, &i);
		else if (input[i] == ' ' || input[i] == '\t')
			handle_spaces(minishell, &tokens, input, &i);
		else
			handle_commands(minishell, &tokens, input, &i);
		i++;
	}
	tmp = tokens;
	while (tmp)
	{
		printf("|token : %s -> type : %d|\n", tmp->token, tmp->type);
		tmp = tmp->next;
	}
}
