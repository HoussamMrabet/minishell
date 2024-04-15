/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:51:44 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/15 09:02:54 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// void	parser(char *input)
// {
	
// }

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	// atexit(leaks);
	char	*input;

	(1) && (input = NULL, rl_catch_signals = 0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	if (argc != 1)
		return (write(2, "No arguments pls\n", 17), 1);
	while (1)
	{
		free(input);
		input = readline("minishell > ");
		if (!input)
		{
			write(1, "exit\n", 6);
			rl_clear_history();
			break ;
		}
		if (*input)
			add_history(input);
		parser(input);
	}
	free(input);
	return (0);
}
