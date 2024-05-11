/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:50:25 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/11 20:09:12 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	seprate_env(t_minishell *minishell, char *exp)
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
	set_fake_env_value(minishell, var, val);
}

void	ft_export(t_minishell *minishell, char *cmd)
{
	char	**splited;
	int		i;

	i = 1;
	splited = ft_split(cmd, '\n', &minishell->local);
	while (splited[i])
	{
		if (!ft_strchr(splited[i], '='))
		{
			set_env_value(minishell, splited[i], "");
		}
		else
		{
			seprate_env(minishell, splited[i]);
		}
		i++;
	}
}