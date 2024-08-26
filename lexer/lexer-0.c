/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:31:22 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/09 05:38:25 by hmrabet          ###   ########.fr       */
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

int	lexer(t_minishell *minishell, char *input)
{
	int			i;

	(1) && (i = -1, minishell->tokens = NULL);
	if (format_invalid(minishell, input) || syntax_invalid(minishell, input))
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
