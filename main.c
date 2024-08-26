/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:51:44 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 16:15:13 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input(t_minishell *minishell)
{
	int	secured_input;

	if (!minishell->input[0])
		return (1);
	if (lexer(minishell, minishell->input)
		|| check_op_syntax(minishell))
	{
		exit_status(258, TRUE);
		ft_putstr_fd(minishell->err.msg, 2);
		secured_input = dup(0);
		signal(SIGINT, heredoc_signal);
		here_doc_err(minishell, minishell->input);
		heredoc_status(0, TRUE);
		dup2(secured_input, 0);
		close(secured_input);
		tcgetattr(STDIN_FILENO, &minishell->termios);
		return (1);
	}
	if (parser(minishell))
		return (1);
	add_pipes(minishell->tree, 0, 1, minishell);
	execute_all(minishell->tree, minishell);
	return (0);
}

static void	check_tty(void)
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_putstr_fd("minishell: unsecured source!\n", 2);
		exit(1);
	}
}

int	main(int c, char **v, char **env)
{
	t_minishell			minishell;

	(1) && (c = 0, v = NULL, rl_catch_signals = 0);
	check_tty();
	init_data(&minishell, env);
	tcgetattr(STDIN_FILENO, &minishell.termios);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		ft_free(&minishell.local);
		close_fds(&minishell);
		minishell.input = ft_readline(&minishell, "minishell >$ ", TRUE);
		if (!minishell.input)
			return (write(1, "\x1B[Fminishell >$ exit\n", 21),
				ft_free_all(&minishell),
				rl_clear_history(), exit_status(0, FALSE));
		if (minishell.input)
		{
			if (handle_input(&minishell))
				continue ;
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &minishell.termios);
	}
	return (ft_free_all(&minishell), close_fds(&minishell), 0);
}
