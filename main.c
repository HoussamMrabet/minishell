/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:51:44 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/20 15:37:35 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_minishell	minishell;

	(1) && (input = NULL, rl_catch_signals = 0);
	init_data(&minishell, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	if (argc != 1)
		return (ft_free(&minishell.garbage), ft_putstr_fd(argv[1], 2),
			ft_putstr_fd(": No such file or directory\n", 2), 127);
	while (1)
	{
		free(input);
		input = readline("minishell >$ ");
		if (!input)
		{
			write(1, "exit\n", 6);
			rl_clear_history();
			break ;
		}
		if (*input)
			add_history(input);
	}
	free(input);
	ft_free(&minishell.garbage);
}
