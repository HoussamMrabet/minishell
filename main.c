/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:51:44 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/27 11:22:48 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int c, char **v, char **env)
{
	char				*input;
	t_minishell			minishell;
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
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (lexer(&minishell, input)
				|| check_op_syntax(&minishell))
			{
				exit_status(258, TRUE);
				ft_putstr_fd("Syntax error !\n", 2);
				ft_free(&minishell.local);
				continue ;
			}
			parser(&minishell);
			// tmp = minishell.tokens;
			// while (tmp)
			// {
			// 	printf("|token : %s -> type : %d|\n", tmp->token, tmp->type);
			// 	tmp = tmp->next;
			// }
			// while (minishell.env[c])
			// {
			// 	printf("%s\n", minishell.env[c]);
			// 	c++;
			// }
			// c = 0;
		}
	}
	free(input);
	ft_free(&minishell.global);
	ft_free(&minishell.local);
	return (exit_status(0, FALSE));
}
