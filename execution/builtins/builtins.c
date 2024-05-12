/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:11:51 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/12 20:55:36 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_minishell *minishell, char *cmd)
{
	char	**splited_cmd;

	splited_cmd = ft_split(cmd, '\n', &minishell->local);
	if (!splited_cmd)
		ft_exit("Allocation error", 1, minishell);
	if (!ft_strcmp(splited_cmd[0], "env"))
		return (ft_env(minishell), 0);
	else if (!ft_strcmp(splited_cmd[0], "echo"))
		return (ft_echo(minishell, cmd), 0);
	else if (!ft_strcmp(splited_cmd[0], "export"))
		return (ft_export(minishell, cmd), 0);
	else if (!ft_strcmp(splited_cmd[0], "unset"))
		return (ft_unset(minishell, cmd), 0);
	else if (!ft_strcmp(splited_cmd[0], "cd"))
		return (ft_cd(minishell, cmd), 0);
	return (1);
}
