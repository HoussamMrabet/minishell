/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:11:51 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/09 14:29:18 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_builtins(t_minishell *minishell, char *cmd)
{
	char	**splited_cmd;

	splited_cmd = ft_split(cmd, ' ', &minishell->local);
	if (!splited_cmd)
		ft_exit("Allocation error", 1, minishell);
	if (!ft_strcmp(splited_cmd[0], "env"))
		ft_env(minishell);
	else if (!ft_strcmp(splited_cmd[0], "echo"))
		ft_echo(minishell, cmd);
}
