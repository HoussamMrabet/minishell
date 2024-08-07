/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:41:01 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/16 14:01:37 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_readline(t_minishell *minishell, char *input, t_bool add)
{
	char	*res;
	char	*in;

	res = readline(input);
	if (!res)
		return (NULL);
	in = ft_strdup(res, minishell, &minishell->local);
	free(res);
	if (add)
		add_history(in);
	return (in);
}

void	*ft_getcwd(t_minishell *minishell)
{
	char	*cwd;
	char	*res;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_exit("getcwd failed", 1, minishell);
	res = ft_strdup(cwd, minishell, &minishell->local);
	free(cwd);
	return (res);
}

void	close_fds(t_minishell *minishell)
{
	int	fd;

	fd = minishell->max_fd;
	while (fd >= 3)
	{
		close(fd);
		fd--;
	}
	minishell->max_fd = 2;
}
