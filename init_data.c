/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:18:07 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/21 11:23:00 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_paths(t_minishell *minishell)
{
	char	**res;
	char	*env;

	env = get_env_value(minishell, "PATH");
	if (!env)
		ft_exit("Allocation error", 1, &minishell->garbage);
	res = splitpaths(env, ':', &minishell->garbage);
	if (!res)
	{
		free(env);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	free (env);
	return (res);
}

static void	ft_get_level(t_minishell *minishell)
{
	int		lvl;
	char	*tmp;

	tmp = get_env_value(minishell, "SHLVL");
	if (!tmp)
		ft_exit("Allocation error", 1, &minishell->garbage);
	lvl = ft_atoi(tmp);
	free(tmp);
	lvl++;
	tmp = ft_itoa(lvl);
	if (!tmp)
		ft_exit("Allocation error", 1, &minishell->garbage);
	set_env_value(minishell, "SHLVL", tmp);
	minishell->shell_level = lvl;
	free(tmp);
}

void	init_data(t_minishell *minishell, char **env)
{
	minishell->garbage = NULL;
	minishell->env = NULL;
	minishell->exit_status = 0;
	env = NULL;
	if (!env || !*env)
		init_custom_env(minishell);
	else
		init_default_env(minishell, env);
	minishell->paths = ft_get_paths(minishell);
	ft_get_level(minishell);
}
