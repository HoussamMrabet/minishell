/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:11:00 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/09 14:34:56 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_minishell *minishell)
{
	t_tokenizer	*token;
	char		**cmd;
	char		*delim;

	token = minishell->tokens;
	delim = NULL;
	while (token)
	{
		if (token->type == DELIMITER)
		{
			token = token->next;
			cmd = ft_split(token->token, ' ', &minishell->local);
			if (!cmd)
				ft_exit("Allocation error", 1, minishell);
			while (1)
			{
				free(delim);
				delim = readline("> ");
				if (!delim || !ft_strcmp(delim, cmd[0]))
					break ;
			}
		}
		token = token->next;
	}
}
