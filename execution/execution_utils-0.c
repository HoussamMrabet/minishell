/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils-0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:02:14 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/26 18:02:43 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_fds_child_btn(int fdin, int fdout, t_exec *tree)
{
	if (fdin == tree->fdin && fdout == tree->fdout)
		return (0);
	if (fdin != tree->fdin && fdin != 0)
		return (catch_error_builtin(close(fdin), "close"), 1);
	else if (fdout != tree->fdout && fdout != 1)
		return (catch_error_builtin(close(fdout), "close"), 1);
	return (0);
}

void	catch_error_builtin(int i, char *command)
{
	if (i != 0)
	{
		if (i == 127 || i == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		else if (i == 126)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
		}
		exit_status(i, 1);
	}
}
