/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:13:57 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/09 16:00:09 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_commands(t_minishell *minishell)
{
	t_tokenizer	*tokens;

	here_doc(minishell);
	tokens = minishell->tokens;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			check_builtins(minishell, tokens->token);
		}
		tokens = tokens->next;
	}
}
