/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:45:30 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/26 17:48:12 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_minishell *m, t_exec *tree)
{
	char	*pwd;

	if (open_files_builtin(tree))
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = m->pwd;
		if (!pwd || !pwd[0])
		{
			write(2, "pwd: error retrieving current directory:", 40);
			perror(" getcwd: cannot access parent directories");
		}
		else
		{
			ft_putstr_fd(pwd, tree->fdout);
			ft_putstr_fd("\n", tree->fdout);
		}
	}
	else
	{
		ft_putstr_fd(pwd, tree->fdout);
		ft_putstr_fd("\n", tree->fdout);
		free(pwd);
	}
}
