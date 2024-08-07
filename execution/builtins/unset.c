/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 05:25:47 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 18:57:00 by hmrabet          ###   ########.fr       */
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

static void	handle_unset(t_minishell *m, char *splited, int *status)
{
	if (splited[0] == 2)
		splited[0] = '\0';
	if (!check_syntax(splited))
	{
		if (!ft_strcmp(splited, "PATH"))
			m->paths = ft_split_global("empty", ':', m);
		remove_env(m, splited);
		remove_fake_env(m, splited);
	}
	else
	{
		*status = 1;
		printf("minishell: unset: `%s': not a valid identifier\n", splited);
	}
}

void	ft_unset(t_minishell *minishell, char *cmd)
{
	char	**splited;
	int		i;
	int		status;
	char	*sub;

	(1) && (status = 0, i = 0);
	while (cmd[i])
	{
		if (cmd[i] == '\n' && (cmd[i + 1] == '\n' || !cmd[i + 1]))
			(1) && (sub = ft_substr(minishell, cmd, 0, i),
			sub = ft_strjoin(sub, "\n\002", minishell, &minishell->local),
			cmd = ft_strjoin(sub, cmd + i + 1, minishell, &minishell->local));
		i++;
	}
	(1) && (splited = ft_split_global(cmd, '\n', minishell), i = 1);
	while (splited[i])
	{
		handle_unset(minishell, splited[i], &status);
		i++;
	}
	exit_status(status, TRUE);
}
