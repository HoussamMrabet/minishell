/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:50:25 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/12 09:37:01 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//export => values between ""
//export var+=val
//export l= => l=""
//export l => l

#include "minishell.h"

static int	check_syntax(char *var)
{
	int	i;

	i = 0;
	if (!var[i] || (!ft_isal(var[i]) && var[i] != '_'))
		return (1);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			return (1);
		i++;
	}
	return (0);
}


static void	separate_env(t_minishell *minishell, char *exp)
{
	int		i;
	char	*var;
	char	*val;
	
	i = 0;
	while (exp[i] && exp[i] != '=')
		i++;
	var = ft_malloc(&minishell->local, i + 1);
	i = 0;
	while (exp[i] && exp[i] != '=')
	{
		var[i] = exp[i];
		i++;
	}
	var[i] = '\0';
	i++;
	val = ft_strdup(exp + i, &minishell->local);
	set_env_value(minishell, var, val);
}

void	ft_export(t_minishell *minishell, char *cmd)
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
	if (!splited[i])
	{
		i = 0;
		while (minishell->env[i])
		{
			printf("declare -x %s\n", minishell->env[i]);
			i++;
		}
	}
	else
	{
		while (splited[i])
		{
			if (splited[i][0] == 2)
				splited[i][0] = '\0';
			if (!check_syntax(splited[i]))
			{
				if (!ft_strchr(splited[i], '='))
					set_env_value(minishell, splited[i], "");
				else
					separate_env(minishell, splited[i]);
			}
			else
			{
				status = 1;
				printf("minishell: export: `%s': not a valid identifier\n", splited[i]);
			}
			i++;
		}
	}
	exit_status(status, TRUE);
}
