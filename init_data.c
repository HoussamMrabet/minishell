/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:18:07 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/12 09:20:27 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_paths(t_minishell *minishell)
{
	char	**res;
	char	*path;

	if (minishell->custom_env)
		path = ft_strdup(_PATH_STDPATH, &minishell->global);
	else
		path = get_env_value(minishell, "PATH");
	if (!path)
		ft_exit("Allocation error", 1, minishell);
	res = splitpaths(path, ':', &minishell->global);
	if (!res)
		ft_exit("Allocation error", 1, minishell);
	return (res);
}

static void	ft_get_level(t_minishell *minishell)
{
	int		lvl;
	char	*tmp;

	tmp = get_env_value(minishell, "SHLVL");
	if (!tmp)
		ft_exit("Allocation error", 1, minishell);
	lvl = ft_atoi(tmp);
	lvl++;
	tmp = ft_itoa(&minishell->local, lvl);
	if (!tmp)
		ft_exit("Allocation error", 1, minishell);
	set_env_value(minishell, "SHLVL", tmp);
	minishell->lvl = lvl;
}

void	init_data(t_minishell *minishell, char **env)
{
	minishell->global = NULL;
	minishell->local = NULL;
	minishell->env = NULL;
	minishell->fake_env = NULL;
	minishell->custom_env = FALSE;
	if (!env || !*env)
	{
		minishell->custom_env = TRUE;
		init_custom_env(minishell);
	}
	else
		init_default_env(minishell, env);
	minishell->paths = ft_get_paths(minishell);
	ft_get_level(minishell);
	ft_free(&minishell->local);
}
