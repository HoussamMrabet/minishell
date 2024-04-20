/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:53:45 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/20 14:04:59 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_default_env(t_minishell *minishell, char **env)
{
	int	i;

	i = ft_arrlen(env);
	minishell->env = (char **)ft_malloc(&minishell->garbage,
			sizeof(char *) * (i + 1));
	if (!minishell->env)
		ft_exit("Allocation error", 1, &minishell->garbage);
	i = 0;
	while (env[i])
	{
		minishell->env[i] = ft_strdup(env[i], &minishell->garbage);
		if (!minishell->env[i])
			ft_exit("Allocation error", 1, &minishell->garbage);
		i++;
	}
	minishell->env[i] = NULL;
}

void	init_custom_env(t_minishell *minishell)
{
	char	*cwd;

	minishell->env = ft_malloc(&minishell->garbage, sizeof(char *) * 5);
	if (!minishell->env)
		ft_exit("Allocation error", 1, &minishell->garbage);
	(1) && (cwd = NULL, cwd = getcwd(NULL, 0));
	minishell->env[0] = ft_strjoin("PATH=", _PATH_STDPATH, &minishell->garbage);
	minishell->env[1] = ft_strjoin("PWD=", cwd, &minishell->garbage);
	minishell->env[2] = ft_strjoin("OLDPWD=", cwd, &minishell->garbage);
	free(cwd);
	minishell->env[3] = ft_strjoin("SHLVL=", "1", &minishell->garbage);
	minishell->env[4] = NULL;
	if (!cwd || minishell->env[0] || !minishell->env[1] || !minishell->env[2]
		|| !minishell->env[3] || !minishell->env)
		ft_exit("Allocation error", 1, &minishell->garbage);
}

char	*get_env_value(t_minishell *minishell, char *str)
{
	size_t	i;
	size_t	j;
	char	*var;

	i = -1;
	while (minishell->env[++i])
	{
		j = 0;
		while (minishell->env[i][j] && minishell->env[i][j] != '=')
			j++;
		var = ft_substr(minishell->env[i], 0, j);
		if (!var)
			return (NULL);
		if (is_equal(str, var) && ft_strlen(str) == j)
		{
			free(var);
			var = ft_substr(minishell->env[i], j + 1,
					ft_strlen(minishell->env[i]) - j);
			if (!var)
				return (NULL);
			return (var);
		}
		free(var);
	}
	return (NULL);
}
