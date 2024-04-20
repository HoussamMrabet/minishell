/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:51:44 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/20 09:59:42 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

static void	init_data(t_minishell *minishell, char **env)
{
	minishell->garbage = NULL;
	minishell->env = NULL;
	if (!*env || !env)
		init_custom_env(minishell);
	else
		init_default_env(minishell, env);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_minishell	minishell;

	// atexit(leaks);
	(1) && (input = NULL, rl_catch_signals = 0);
	init_data(&minishell, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	if (argc != 1)
		return (ft_putstr_fd(argv[1], 2),
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
}
