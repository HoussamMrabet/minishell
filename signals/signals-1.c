/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals-1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:04:41 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/24 16:56:23 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_status(int new_stat, t_bool to_set)
{
	static int	stat;

	if (to_set)
		stat = new_stat;
	return (stat);
}

void	signals_handle(t_minishell *mini, t_exec *tree)
{
	if (tree->tokens && ft_get_path(mini, tree->tokens)
		&& ft_strnstr(tree->tokens->token, "minishell",
			ft_strlen(tree->tokens->token))
		&& !ft_strncmp(tree->tokens->token
			+ (ft_strlen(tree->tokens->token) - 9), "minishell", 10))
		signal(SIGINT, child_minishell_handler);
	else
	{
		signal(SIGQUIT, handle_quit);
		signal(SIGINT, child_handler);
	}
}
