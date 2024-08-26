/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 05:53:42 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 19:22:03 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_fake_env2(t_minishell *m, char *var, int k)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env = ft_malloc(m, &m->global, sizeof(char *) * (k + 1));
	while (m->fake_env[i])
	{
		if (starts_with(var, m->fake_env[i]))
		{
			i++;
			continue ;
		}
		(1) && (env[j] = m->fake_env[i], i++, j++);
	}
	(1) && (env[j] = NULL, m->fake_env = env);
}

void	remove_fake_env(t_minishell *m, char *var)
{
	int		i;
	int		j;

	(1) && (j = 0, i = 0);
	while (m->fake_env[i] && !(starts_with(var, m->fake_env[i])))
		i++;
	if (!m->fake_env[i])
		return ;
	i = 0;
	while (m->fake_env[i])
	{
		if (starts_with(var, m->fake_env[i]))
		{
			i++;
			continue ;
		}
		(1) && (i++, j++);
	}
	remove_fake_env2(m, var, j);
}

static void	remove_env2(t_minishell *m, char *var, int k)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	(1) && (new_env = ft_malloc(m, &m->global,
			sizeof(char *) * (k + 1)), j = 0, i = 0);
	while (m->env[i])
	{
		if (starts_with(var, m->env[i]))
		{
			i++;
			continue ;
		}
		(1) && (new_env[j] = m->env[i], i++, j++);
	}
	(1) && (new_env[j] = NULL, m->env = new_env);
}

void	remove_env(t_minishell *m, char *var)
{
	int		i;
	int		j;

	(1) && (j = 0, i = 0);
	while (m->env[i] && !(starts_with(var, m->env[i])))
		i++;
	if (!m->env[i])
		return ;
	i = 0;
	while (m->env[i])
	{
		if (starts_with(var, m->env[i]))
		{
			i++;
			continue ;
		}
		i++;
		j++;
	}
	remove_env2(m, var, j);
}
