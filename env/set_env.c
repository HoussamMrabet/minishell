/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:56:41 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/11 18:56:47 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (value[0])
		set_fake_env_value(minishell, env, value);
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

void	set_fake_env_value(t_minishell *minishell, char *env, char *value)
{
	int	i;

	i = 0;
	while (minishell->fake_env[i] && !(starts_with(env, minishell->fake_env[i])))
		i++;
	if (!minishell->fake_env[i])
		return ;
	minishell->fake_env[i] = ft_malloc(&minishell->global,
			sizeof(char) * (ft_strlen(env) + ft_strlen(value) + 2));
	if (!minishell->fake_env[i])
		ft_exit("Allocation error", 1, minishell);
	ft_strlcpy(minishell->fake_env[i], env, ft_strlen(env) + 1);
	ft_strlcat(minishell->fake_env[i], "=", ft_strlen(minishell->fake_env[i]) + 2);
	ft_strlcat(minishell->fake_env[i], value,
		ft_strlen(minishell->fake_env[i]) + ft_strlen(value) + 1);
}
