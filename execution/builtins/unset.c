/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 05:25:47 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/12 08:05:55 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax(char *var)
{
	int	i;

	i = 0;
	if (!var[i] || (!ft_isal(var[i]) && var[i] != '_'))
		return (1);
	i++;
	while (var[i])
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(t_minishell *minishell, char *cmd)
{
	char	**splited;
	int		i;
	int		status;
	char	*sub;

	status = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\n' && (cmd[i + 1] == '\n' || !cmd[i + 1]))
		{
			sub = ft_substr(&minishell->local, cmd, 0, i);
			sub = ft_strjoin(sub, "\n\002", &minishell->local);
			cmd = ft_strjoin(sub, cmd + i + 1, &minishell->local);
		}
		i++;
	}
	splited = ft_split(cmd, '\n', &minishell->local);
	i = 1;
	while (splited[i])
	{
		if (splited[i][0] == 2)
			splited[i][0] = '\0';
		if (!check_syntax(splited[i]))
		{
			remove_env(minishell, splited[i]);
			remove_fake_env(minishell, splited[i]);
		}
		else
		{
			status = 1;
			printf("minishell: unset: `%s': not a valid identifier\n", splited[i]);
		}
		i++;
	}
	exit_status(status, TRUE);
}
