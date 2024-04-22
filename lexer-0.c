/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:31:22 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/22 11:12:05 by hmrabet          ###   ########.fr       */
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

static t_bool	check_content(char *input, int i)
{
	t_bool	is_empty;
	
	is_empty = TRUE;
	while (input[++i])
	{
		if (input[i] == ')')
			break ;
		if (input[i] != ' ' && input[i] != '\t')
			is_empty = FALSE;
	}
	return (is_empty);
}

static t_bool	format_invalid(char *input)
{
	t_bool	q[2];
	int		i[3];

	(1) && (i[2] = 0, q[0] = FALSE, q[1] = FALSE, i[0] = 0, i[1] = -1);
	while (input[++i[1]])
	{
		if (input[i[1]] == '\'')
		{
			if (q[0])
				q[0] = FALSE;
			else if (!q[0] && !q[1])
				q[0] = TRUE;
		}
		else if (input[i[1]] == '"')
		{
			if (q[1])
				q[1] = FALSE;
			else if (!q[0] && !q[1])
				q[1] = TRUE;
		}
		(input[i[1]] == '(' && !q[0] && !q[1]) && (i[0]++, i[2] = check_content(input, i[1]));
		(input[i[1]] == ')' && !q[0] && !q[1]) && (i[0]--);
	}
	return (q[0] || q[1] || i[0] || i[2]);
}

int	lexer(t_minishell *minishell, char *input)
{
	int			i;

	(1) && (i = -1, minishell->tokens = NULL);
	if (format_invalid(input) || syntax_invalid(input))
		return (1);
	while (input[++i])
	{
		if (input[i] == '\'')
			handle_single_quotes(minishell, &minishell->tokens, input, &i);
		else if (input[i] == '"')
			handle_double_quotes(minishell, &minishell->tokens, input, &i);
		else if (input[i] == '<' || input[i] == '>')
			handle_red_and_del(minishell, &minishell->tokens, input, &i);
		else if (input[i] == '|')
			handle_pipe_or_sign(minishell, &minishell->tokens, input, &i);
		else if (input[i] == '&' && input[i + 1] == '&')
			handle_and_sign(minishell, &minishell->tokens, input, &i);
		else if (input[i] == ' ' || input[i] == '\t')
			handle_spaces(minishell, &minishell->tokens, input, &i);
		else if (input[i] == '(' || input[i] == ')')
			handle_paranthese(minishell, &minishell->tokens, input, &i);
		else
			handle_commands(minishell, &minishell->tokens, input, &i);
	}
	return (0);
}
