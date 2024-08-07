/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:49:10 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/16 13:31:25 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_node_for_execute(t_minishell *minishell, t_exec *node)
{
	t_tokenizer	*tokens;

	tokens = node->tokens;
	replace_expand_values(minishell, &tokens);
	separate_wildcards(&tokens);
	merge_tokens(minishell, &tokens);
	split_commands(minishell, &tokens);
	ft_wildcards(minishell);
	merge_wildcards(minishell);
	set_io_tokens(minishell, &node);
}
