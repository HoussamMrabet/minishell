/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 06:41:00 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/23 19:09:53 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_text_expand(t_minishell *minishell, char **tokens)
{
	int			i;
	int			j;
	char		*tmp;
	char		*value;
	t_bool		first;

	first = TRUE;
	i = 0;
	j = 0;
	value = ft_strdup("", &minishell->tmp);
	while ((*tokens)[i])
	{
		if ((*tokens)[i] == '$')
		{
			// if (first && i != 0)
			// {
			// 	value = ft_substr(&minishell->tmp, (*tokens), 0, i - 1);
			// 	first = FALSE;
			// }
			if (!(*tokens)[i + 1])
				value = ft_strjoin(value, "$", &minishell->tmp);
			else if ((*tokens)[i + 1] == '$')
			{
				value = ft_strjoin(value, ft_itoa(&minishell->tmp, 32467), &minishell->tmp);
				i++;
			}
			else
			{
				j = 1;
				while ((*tokens)[i + j] && (*tokens)[i + j] != '$')
					j++;
				j--;
				tmp = get_env_value(minishell, ft_substr(&minishell->tmp, (*tokens) + (i + 1), 0, j));
				if (!tmp)
					tmp = ft_strdup("", &minishell->tmp);
				value = ft_strjoin(value, tmp, &minishell->tmp);
				i += j;
			}
		}
		else
		{
			j = 0;
			while ((*tokens)[i + j] && (*tokens)[i + j] != '$')
				j++;
			tmp = ft_substr(&minishell->tmp, (*tokens) + i, 0, j);
			value = ft_strjoin(value, tmp, &minishell->tmp);
			i += j - 1;
		}
		i++;
	}
	*tokens = value;
}

void	replace_expand_values(t_minishell *minishell, t_tokenizer **tokens)
{
	t_tokenizer	*token;

	token = *tokens;
	while (token)
	{
		if (token->type == TEXT)
			handle_text_expand(minishell, &token->token);
		// else if (token->type == D_QUOTE)
		// 	handle_quote_expand();
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
	minishell->cmdlist = NULL;
	while (tokens)
	{
		printf("token : %s\n", tokens->token);
		tokens = tokens->next;
	}
}
