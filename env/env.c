/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:53:45 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/23 15:43:26 by hmrabet          ###   ########.fr       */
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
		ft_exit("Allocation error", 1, minishell);
	i = 0;
	while (env[i])
	{
		minishell->env[i] = ft_strdup(env[i], &minishell->garbage);
		if (!minishell->env[i])
			ft_exit("Allocation error", 1, minishell);
		i++;
	}
	minishell->env[i] = NULL;
}

void	init_custom_env(t_minishell *minishell)
{
	char	*cwd;

	minishell->env = ft_malloc(&minishell->garbage, sizeof(char *) * 5);
	if (!minishell->env)
		ft_exit("Allocation error", 1, minishell);
	(1) && (cwd = NULL, cwd = getcwd(NULL, 0));
	minishell->env[0] = ft_strjoin("PATH=", _PATH_STDPATH, &minishell->garbage);
	minishell->env[1] = ft_strjoin("PWD=", cwd, &minishell->garbage);
	minishell->env[2] = ft_strjoin("OLDPWD=", cwd, &minishell->garbage);
	free(cwd);
	minishell->env[3] = ft_strjoin("SHLVL=", "1", &minishell->garbage);
	minishell->env[4] = NULL;
	if (!minishell->env[0] || !minishell->env[1] || !minishell->env[2]
		|| !minishell->env[3] || !minishell->env)
		ft_exit("Allocation error", 1, minishell);
}

static int	starts_with(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0')
		return (i + 1);
	return (0);
}

void	set_env_value(t_minishell *minishell, char *env, char *value)
{
	int	i;

	i = 0;
	while (minishell->env[i] && !(starts_with(env, minishell->env[i])))
		i++;
	if (!minishell->env[i])
		return ;
	minishell->env[i] = ft_malloc(&minishell->garbage,
			sizeof(char) * (ft_strlen(env) + ft_strlen(value) + 2));
	if (!minishell->env[i])
		ft_exit("Allocation error", 1, minishell);
	ft_strlcpy(minishell->env[i], env, ft_strlen(env) + 1);
	ft_strlcat(minishell->env[i], "=", ft_strlen(minishell->env[i]) + 2);
	ft_strlcat(minishell->env[i], value,
		ft_strlen(minishell->env[i]) + ft_strlen(value) + 1);
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
		var = ft_substr(&minishell->tmp, minishell->env[i], 0, j);
		if (!var)
			return (NULL);
		if (is_equal(str, var) && ft_strlen(str) == j)
		{
			var = ft_substr(&minishell->tmp, minishell->env[i], j + 1,
					ft_strlen(minishell->env[i]) - j);
			if (!var)
				return (NULL);
			return (var);
		}
	}
	return (NULL);
}
