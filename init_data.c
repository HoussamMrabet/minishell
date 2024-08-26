/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:18:07 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/26 19:44:20 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_paths(t_minishell *minishell)
{
	char	**res;
	char	*path;

	if (minishell->paths)
		return (minishell->paths);
	if (minishell->custom_env)
		path = ft_strdup(_PATH_STDPATH, minishell, &minishell->global);
	else
		path = get_env_value(minishell, "PATH");
	if (!path)
		path = ft_strdup(_PATH_STDPATH, minishell, &minishell->global);
	res = splitpaths(path, ':', minishell);
	return (res);
}

static void	ft_get_level(t_minishell *minishell)
{
	int		lvl;
	char	*tmp;

	tmp = get_env_value(minishell, "SHLVL");
	if (!tmp || !tmp[0])
	{
		lvl = 0;		
		tmp = ft_itoa(minishell, &minishell->local, 0);
	}
	else
	{
		lvl = ft_atoi(tmp);
		if (lvl >= 999)
			tmp = ft_strdup("", minishell, &minishell->global);
		else
		{
			lvl++;
			tmp = ft_itoa(minishell, &minishell->local, lvl);
		}
	}
	set_env_value(minishell, "SHLVL", tmp);
	set_fake_env_value(minishell, "SHLVL", tmp);
	minishell->lvl = lvl;
}

void	init_data(t_minishell *minishell, char **env)
{
	minishell->max_fd = 2;
	minishell->global = NULL;
	minishell->local = NULL;
	minishell->env = NULL;
	minishell->fake_env = NULL;
	minishell->paths = NULL;
	minishell->tokens = NULL;
	minishell->tree = NULL;
	minishell->home = NULL;
	minishell->err.msg = NULL;
	minishell->_ = NULL;
	minishell->pwd = NULL;
	minishell->custom_env = FALSE;
	minishell->input = NULL;
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
