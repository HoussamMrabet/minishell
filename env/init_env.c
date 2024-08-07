/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:53:45 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 13:51:04 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_default_env(t_minishell *m, char **env)
{
	int	i;

	i = ft_arrlen(env);
	m->env = (char **)ft_malloc(m, &m->global,
			sizeof(char *) * (i + 1));
	m->fake_env = (char **)ft_malloc(m, &m->global,
			sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		m->env[i] = ft_strdup(env[i], m, &m->global);
		m->fake_env[i] = ft_strdup(env[i], m, &m->global);
		i++;
	}
	m->env[i] = NULL;
	m->fake_env[i] = NULL;
	m->_ = get_env_value(m, "_");
}

void	init_custom_env(t_minishell *m)
{
	char	*cwd;

	m->env = ft_malloc(m, &m->global, sizeof(char *) * 4);
	m->fake_env = ft_malloc(m, &m->global, sizeof(char *) * 4);
	(1) && (cwd = NULL, cwd = ft_getcwd(m));
	m->env[0] = ft_strjoin("OLDPWD", "", m, &m->global);
	m->env[1] = ft_strjoin("PWD=", cwd, m, &m->global);
	m->env[2] = ft_strjoin("SHLVL=", "1", m, &m->global);
	m->env[3] = NULL;
	m->_ = ft_strjoin(cwd, "/./minishell", m, &m->global);
	m->fake_env[0] = ft_strjoin("PWD=", cwd, m, &m->global);
	m->fake_env[1] = ft_strjoin("SHLVL=", "1", m, &m->global);
	m->fake_env[2] = ft_strjoin("_=", m->_, m, &m->global);
	m->fake_env[3] = NULL;
}
