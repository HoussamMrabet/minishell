/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals-0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:56:56 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/22 23:04:59 by hmrabet          ###   ########.fr       */
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
		exit_status(1, TRUE);
	}
}

void	child_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		exit_status(130, TRUE);
	}
}

void	handle_quit(int signal)
{
	if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_replace_line("", 0);
		rl_on_new_line();
		exit_status(131, TRUE);
	}
}

void	child_minishell_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		exit_status(1, TRUE);
	}
}

void	heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		close(0);
		heredoc_status(1, TRUE);
		exit_status(1, TRUE);
	}
}
