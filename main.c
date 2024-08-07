/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:51:44 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/18 09:59:15 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int c, char **v, char **env)
{
	t_minishell			minishell;

	(1) && (c = 0, v = NULL, rl_catch_signals = 0);
	init_data(&minishell, env);
	handle_signals();
	while (1)
	{
		ft_free(&minishell.local);
		close_fds(&minishell);
		minishell.input = ft_readline(&minishell, "minishell >$ ", TRUE);
		if (!minishell.input)
			return (write(1, "exit\n", 6), ft_free_all(&minishell),
				rl_clear_history(), exit_status(0, FALSE));
		if (*minishell.input)
		{
			if (lexer(&minishell, minishell.input)
				|| check_op_syntax(&minishell))
			{
				exit_status(258, TRUE);
				ft_putstr_fd(minishell.err.msg, 2);
				here_doc_err(&minishell, minishell.input);
			}
			parser(&minishell);
			add_pipes(minishell.tree, 0 , 1, &minishell);
			execute_all(minishell.tree, &minishell);
		}
	}
	ft_free_all(&minishell);
	close_fds(&minishell);
}
