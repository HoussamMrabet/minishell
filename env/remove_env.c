/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 05:53:42 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/12 12:29:43 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_fake_env(t_minishell *minishell, char *var)
{
	int		i;
	int		j;
	char	**new_env;

	(1) && (j = 0, i = 0);
	while (minishell->fake_env[i]
		&& !(starts_with(var, minishell->fake_env[i])))
		i++;
	if (!minishell->fake_env[i])
		return ;
	i = 0;
	while (minishell->fake_env[i])
	{
		if (starts_with(var, minishell->fake_env[i]))
		{
			i++;
			continue ;
		}
		(1) && (i++, j++);
	}
	(1) && (new_env = ft_malloc(&minishell->global,
			sizeof(char *) * (j + 1)), j = 0, i = 0);
	while (minishell->fake_env[i])
	{
		if (starts_with(var, minishell->fake_env[i]))
		{
			i++;
			continue ;
		}
		(1) && (new_env[j] = minishell->fake_env[i], i++, j++);
	}
	(1) && (new_env[j] = NULL, minishell->fake_env = new_env);
}

void	remove_env(t_minishell *minishell, char *var)
{
	int		i;
	int		j;
	char	**new_env;

	(1) && (j = 0, i = 0);
	while (minishell->env[i] && !(starts_with(var, minishell->env[i])))
		i++;
	if (!minishell->env[i])
		return ;
	i = 0;
	while (minishell->env[i])
	{
		if (starts_with(var, minishell->env[i]))
		{
			i++;
			continue ;
		}
		i++;
		j++;
	}
	(1) && (new_env = ft_malloc(&minishell->global,
			sizeof(char *) * (j + 1)), j = 0, i = 0);
	while (minishell->env[i])
	{
		if (starts_with(var, minishell->env[i]))
		{
			i++;
			continue ;
		}
		(1) && (new_env[j] = minishell->env[i], i++, j++);
	}
	(1) && (new_env[j] = NULL, minishell->env = new_env);
}
