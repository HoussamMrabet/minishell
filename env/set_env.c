/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:56:41 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 14:06:26 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_fake_env_value(t_minishell *m, char *var, char *val)
{
	char	**env;
	char	**new_env;
	int		i;

	i = 0;
	env = m->fake_env;
	while (env[i])
		i++;
	new_env = ft_malloc(m, &m->global, sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strjoin(var, "=", m, &m->local);
	new_env[i] = ft_strjoin(new_env[i], val, m, &m->global);
	i++;
	new_env[i] = NULL;
	m->fake_env = new_env;
}

void	add_env_value(t_minishell *m, char *var, char *val)
{
	char	**env;
	char	**new_env;
	int		i;

	i = 0;
	env = m->env;
	while (env[i])
		i++;
	new_env = ft_malloc(m, &m->global, sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	if (val[0] == '\002')
		new_env[i] = ft_strdup(var, m, &m->global);
	else
	{
		new_env[i] = ft_strjoin(var, "=", m, &m->local);
		new_env[i] = ft_strjoin(new_env[i], val, m, &m->global);
	}
	new_env[++i] = NULL;
	m->env = new_env;
	sort_env(m->env);
}

void	set_env_value(t_minishell *minishell, char *env, char *value)
{
	int	i;

	i = 0;
	while (minishell->env[i] && !(starts_with(env, minishell->env[i])))
		i++;
	if (!minishell->env[i])
	{
		add_env_value(minishell, env, value);
		return ;
	}
	if (value[0] != '\002')
	{
		minishell->env[i] = ft_malloc(minishell, &minishell->global,
				sizeof(char) * (ft_strlen(env) + ft_strlen(value) + 2));
		ft_strlcpy(minishell->env[i], env, ft_strlen(env) + 1);
		ft_strlcat(minishell->env[i], "=", ft_strlen(minishell->env[i]) + 2);
		ft_strlcat(minishell->env[i], value,
			ft_strlen(minishell->env[i]) + ft_strlen(value) + 1);
	}
	sort_env(minishell->env);
}

void	set_fake_env_value(t_minishell *minishell, char *env, char *value)
{
	int	i;

	i = 0;
	while (minishell->fake_env[i]
		&& !(starts_with(env, minishell->fake_env[i])))
		i++;
	if (!minishell->fake_env[i])
	{
		add_fake_env_value(minishell, env, value);
		return ;
	}
	if (value[0] != '\002')
	{
		minishell->fake_env[i] = ft_malloc(minishell, &minishell->global,
				sizeof(char) * (ft_strlen(env) + ft_strlen(value) + 2));
		ft_strlcpy(minishell->fake_env[i],
			env, ft_strlen(env) + 1);
		ft_strlcat(minishell->fake_env[i],
			"=", ft_strlen(minishell->fake_env[i]) + 2);
		ft_strlcat(minishell->fake_env[i], value,
			ft_strlen(minishell->fake_env[i]) + ft_strlen(value) + 1);
	}
}
