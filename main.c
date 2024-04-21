/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:51:44 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/21 12:54:29 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_minishell	minishell;

	// atexit(leaks);
	(1) && (argc = 0, argv = NULL, input = NULL, rl_catch_signals = 0);
	init_data(&minishell, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		free(input);
		input = readline("minishell >$ ");
		if (!input || is_equal(input, "exit"))
		{
			write(1, "exit\n", 6);
			rl_clear_history();
			free(input);
			ft_free(&minishell.garbage);
			exit(minishell.exit_status);
		}
		if (*input)
		{
			add_history(input);
			lexer(&minishell, input);
		}
	}
}
