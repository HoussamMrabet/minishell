/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:18:07 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/20 14:25:11 by hmrabet          ###   ########.fr       */
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

void	init_data(t_minishell *minishell, char **env)
{
	minishell->garbage = NULL;
	minishell->env = NULL;
	if (!*env || !env)
		init_custom_env(minishell);
	else
		init_default_env(minishell, env);
	minishell->paths = ft_get_paths(minishell);
}
