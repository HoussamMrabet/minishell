/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:51:44 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/24 09:54:17 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int c, char **v, char **env)
{
	char			*input;
	t_minishell		minishell;
	// t_tokenizer		*tmp;
	
	// atexit(leaks);
	(1) && (c = 0, v = NULL, input = NULL, rl_catch_signals = 0);
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
			ft_free(&minishell.global);
			exit(minishell.exit_status);
		}
		if (*input)
		{
			add_history(input);
			if (lexer(&minishell, input))
			{
				minishell.exit_status = 258;
				ft_putstr_fd("Syntax error !\n", 2);
				continue ;
			}
			parser(&minishell);
			// tmp = minishell.tokens;
			// while (tmp)
			// {
			// 	printf("|token : %s -> type : %d|\n", tmp->token, tmp->type);
			// 	tmp = tmp->next;
			// }
		}
	}
	free(input);
	ft_free(&minishell.global);
	ft_free(&minishell.local);
}
