/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:51:44 by hmrabet           #+#    #+#             */
/*   Updated: 2024/06/10 22:39:18 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

char	*get_del(char *input)
{
	char	*del;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>' && input[i] != '|' && input[i] != '&' && input[i] != '(' && input[i] != ')')
	{
		if (input[i] != '\'' && input[i] != '"')
			j++;
		i++;
	}
	i = 0;
	del = malloc(j + 1);
	if (!del || j == 0)
		return (NULL);
	j = 0;
	while (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>' && input[i] != '|' && input[i] != '&' && input[i] != '(' && input[i] != ')')
	{
		if (input[i] != '\'' && input[i] != '"')
		{
			del[j] = input[i];
			j++;
		}
		i++;
	}
	del[j] = '\0';
	return (del);
}

void	here_doc_err(char *input)
{
	char	*delim;
	char	*del;
	int		i;

	i = 0;
	del = NULL;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i] == ' ')
				i++;
			delim = get_del(input + i);
			if (delim)
			{
				while (1)
				{
					free(del);
					del = readline("> ");
					if (!del || !ft_strcmp(delim, del))
						break ;
				}
				free(del);
			}
			free(delim);
		}
		i++;
	}
}

int	main(int c, char **v, char **env)
{
	char				*input;
	t_minishell			minishell;

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
				here_doc_err(input);
				ft_free(&minishell.local);
				continue ;
			}
			parser(&minishell);
			run_commands(&minishell);
		}
	}
	free(input);
	ft_free(&minishell.global);
	ft_free(&minishell.local);
	return (exit_status(0, FALSE));
}
