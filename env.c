/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:53:45 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/20 10:11:00 by hmrabet          ###   ########.fr       */
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
	{
		ft_putstr_fd("Allocation error\n", 2);
		ft_free(&minishell->garbage);
		exit(1);
	}
	i = 0;
	while (env[i])
	{
		minishell->env[i] = ft_strdup(env[i], &minishell->garbage);
		if (!minishell->env[i])
		{
			ft_putstr_fd("Allocation error\n", 2);
			ft_free(&minishell->garbage);
			exit(1);
		}
		i++;
	}
	minishell->env[i] = NULL;
}

void	init_custom_env(t_minishell *minishell)
{
	char	*cwd;
	char	*tmp;

	minishell->env = ft_malloc(&minishell->garbage, sizeof(char *) * 5);
	if (!minishell->env)
	{
		ft_putstr_fd("Allocation error\n", 2);
		ft_free(&minishell->garbage);
		exit(1);
	}
	(1) && (cwd = NULL, tmp = getcwd(NULL, 0));
	cwd = ft_strdup(cwd, &minishell->garbage);
	free(tmp);
	minishell->env[0] = ft_strjoin("PATH=", _PATH_STDPATH, &minishell->garbage);
	minishell->env[1] = ft_strjoin("PWD=", cwd, &minishell->garbage);
	minishell->env[2] = ft_strjoin("OLDPWD=", cwd, &minishell->garbage);
	minishell->env[3] = ft_strjoin("SHLVL=", "1", &minishell->garbage);
	minishell->env[4] = NULL;
	if (minishell->env[0] || !minishell->env[1] || !minishell->env[2]
		|| !minishell->env[3] || !minishell->env)
	{
		ft_putstr_fd("Allocation error\n", 2);
		ft_free(&minishell->garbage);
		exit(1);
	}
}
