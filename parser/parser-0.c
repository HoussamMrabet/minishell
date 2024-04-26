/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 06:41:00 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/26 18:41:23 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_tokens(t_minishell *minishell, t_tokenizer **tokens)
{
	t_tokenizer	*token;

	token = *tokens;
	while (token)
	{
		if (token->type == TEXT || token->type == S_QUOTE
			|| token->type == D_QUOTE)
		{
			if (token->next)
			{
				if (token->next->type == TEXT
					|| token->next->type == S_QUOTE
					|| token->next->type == D_QUOTE)
				{
					token->token = ft_strjoin(token->token,
							token->next->token, &minishell->local);
					token->next = token->next->next;
					continue ;
				}
				else if (token->next->type == SPACES)
					token->next = token->next->next;
			}
		}
		token = token->next;
	}
}

void	parser(t_minishell *minishell)
{
	int			i;
	t_tokenizer	*tokens;

	i = 0;
	tokens = minishell->tokens;
	replace_expand_values(minishell, &tokens);
	merge_tokens(minishell, &tokens);
	while (tokens)
	{
		printf("token : %s\n", tokens->token);
		tokens = tokens->next;
	}
}
