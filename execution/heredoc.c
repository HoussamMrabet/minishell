/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:11:00 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/09 16:17:40 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_minishell *minishell)
{
	t_tokenizer	*token;
	char		*delim;

	token = minishell->tokens;
	delim = NULL;
	while (token)
	{
		if (token->type == DELIMITER)
		{
			token = token->next;
			while (1)
			{
				free(delim);
				delim = readline("> ");
				if (!delim || !ft_strcmp(delim, token->token))
					break ;
			}
			free(delim);
		}
		token = token->next;
	}
}
