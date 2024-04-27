/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:31:22 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/27 11:29:48 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		(input[i[1]] == '(' && !q[0] && !q[1])
			&& (i[0]++, i[2] = check_content(input, i[1]));
		(input[i[1]] == ')' && !q[0] && !q[1]) && (i[0]--);
	}
	return (q[0] || q[1] || i[0] || i[2]);
}

int	check_op_syntax(t_minishell *minishell)
{
	t_tokenizer	*t;

	t = minishell->tokens;
	while (t)
	{
		if (t->type == PIPE || t->type == OR || t->type == AND
			|| t->type == IN_RED || t->type == OUT_RED || t->type == DELIMITER
			|| t->type == APPEND || t->type == PARENTHESE)
		{
			while (t)
			{
				if (t->next && t->next->type == SPACES)
					t = t->next;
				else
					break ;
			}
			if (t->next && (t->next->type == PIPE || t->next->type == OR
					|| t->next->type == AND || t->next->type == IN_RED
					|| t->next->type == OUT_RED || t->next->type == DELIMITER
					|| t->next->type == APPEND || t->next->type == PARENTHESE))
				return (1);
		}
		t = t->next;
	}
	return (0);
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
