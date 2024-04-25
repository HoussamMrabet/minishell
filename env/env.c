/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:53:45 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/25 11:37:09 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_default_env(t_minishell *minishell, char **env)
{
	int	i;

	i = ft_arrlen(env);
	minishell->env = (char **)ft_malloc(&minishell->global,
			sizeof(char *) * (i + 1));
	if (!minishell->env)
		ft_exit("Allocation error", 1, minishell);
	i = 0;
	while (env[i])
	{
		minishell->env[i] = ft_strdup(env[i], &minishell->global);
		if (!minishell->env[i])
			ft_exit("Allocation error", 1, minishell);
		i++;
	}
	minishell->env[i] = NULL;
}

void	init_custom_env(t_minishell *minishell)
{
	char	*cwd;

	minishell->env = ft_malloc(&minishell->global, sizeof(char *) * 4);
	minishell->hidden_env = ft_malloc(&minishell->global, sizeof(char *) * 3);
	if (!minishell->env || !minishell->hidden_env)
		ft_exit("Allocation error", 1, minishell);
	(1) && (cwd = NULL, cwd = getcwd(NULL, 0));
	minishell->hidden_env[0] = ft_strjoin("PATH=",
			_PATH_STDPATH, &minishell->global);
	minishell->hidden_env[1] = ft_strjoin("OLDPWD=", cwd, &minishell->global);
	minishell->hidden_env[2] = NULL;
	minishell->env[0] = ft_strjoin("PWD=", cwd, &minishell->global);
	minishell->env[1] = ft_strjoin("SHLVL=", "1", &minishell->global);
	minishell->env[2] = ft_strjoin("_=", ft_strjoin(cwd, "/./minishell",
				&minishell->global), &minishell->global);
	free(cwd);
	minishell->env[3] = NULL;
	if (!minishell->env[0] || !minishell->env[1] || !minishell->env[2]
		|| !minishell->hidden_env[0] || !minishell->hidden_env[1])
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
	minishell->env[i] = ft_malloc(&minishell->global,
			sizeof(char) * (ft_strlen(env) + ft_strlen(value) + 2));
	if (!minishell->env[i])
		ft_exit("Allocation error", 1, minishell);
	ft_strlcpy(minishell->env[i], env, ft_strlen(env) + 1);
	ft_strlcat(minishell->env[i], "=", ft_strlen(minishell->env[i]) + 2);
	ft_strlcat(minishell->env[i], value,
		ft_strlen(minishell->env[i]) + ft_strlen(value) + 1);
}

char	*get_env_value(t_minishell *minishell, char *str, t_bool is_hidden)
{
	size_t	i;
	size_t	j;
	char	*var;
	char	**env;

	(is_hidden) && (env = minishell->hidden_env, i = -1);
	(!is_hidden) && (env = minishell->env, i = -1);
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		var = ft_substr(&minishell->local, env[i], 0, j);
		if (!var)
			return (NULL);
		if (is_equal(str, var) && ft_strlen(str) == j)
		{
			var = ft_substr(&minishell->local, env[i], j + 1,
					ft_strlen(env[i]) - j);
			if (!var)
				return (NULL);
			return (var);
		}
	}
	return (NULL);
}
