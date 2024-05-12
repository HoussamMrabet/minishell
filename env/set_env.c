/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:56:41 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/12 09:24:14 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_fake_env_value(t_minishell *minishell, char *var, char *val)
{
	char	**env;
	char	**new_env;
	int		i;

	i = 0;
	env = minishell->fake_env;
	while (env[i])
		i++;
	new_env = ft_malloc(&minishell->global, sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strjoin(var, "=", &minishell->local);
	new_env[i] = ft_strjoin(new_env[i], val, &minishell->global);
	i++;
	new_env[i] = NULL;
	minishell->fake_env = new_env;
}

void	add_env_value(t_minishell *minishell, char *var, char *val)
{
	char	**env;
	char	**new_env;
	int		i;

	i = 0;
	env = minishell->env;
	while (env[i])
		i++;
	new_env = ft_malloc(&minishell->global, sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	// if (!val[0])
	// 	new_env[i] = ft_strdup(var, &minishell->global);
	// else
	// {
		new_env[i] = ft_strjoin(var, "=", &minishell->local);
		new_env[i] = ft_strjoin(new_env[i], val, &minishell->global);
	// }
	new_env[++i] = NULL;
	minishell->env = new_env;
	sort_env(minishell->env);
}

void	set_env_value(t_minishell *minishell, char *env, char *value)
{
	int	i;

	i = 0;
	if (value[0])
		set_fake_env_value(minishell, env, value);
	while (minishell->env[i] && !(starts_with(env, minishell->env[i])))
		i++;
	if (!minishell->env[i])
	{
		add_env_value(minishell, env, value);
		return ;
	}
	if (value[0])
	{
		minishell->env[i] = ft_malloc(&minishell->global,
				sizeof(char) * (ft_strlen(env) + ft_strlen(value) + 2));
		if (!minishell->env[i])
			ft_exit("Allocation error", 1, minishell);
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
	while (minishell->fake_env[i] && !(starts_with(env, minishell->fake_env[i])))
		i++;
	if (!minishell->fake_env[i])
	{
		add_fake_env_value(minishell, env, value);
		return ;
	}
	if (value[0])
	{
		minishell->fake_env[i] = ft_malloc(&minishell->global,
				sizeof(char) * (ft_strlen(env) + ft_strlen(value) + 2));
		if (!minishell->fake_env[i])
			ft_exit("Allocation error", 1, minishell);
		ft_strlcpy(minishell->fake_env[i], env, ft_strlen(env) + 1);
		ft_strlcat(minishell->fake_env[i], "=", ft_strlen(minishell->fake_env[i]) + 2);
		ft_strlcat(minishell->fake_env[i], value,
			ft_strlen(minishell->fake_env[i]) + ft_strlen(value) + 1);
	}
}
