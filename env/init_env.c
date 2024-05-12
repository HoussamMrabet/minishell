/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:53:45 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/12 09:21:22 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_default_env(t_minishell *minishell, char **env)
{
	int	i;

	i = ft_arrlen(env);
	minishell->env = (char **)ft_malloc(&minishell->global,
			sizeof(char *) * (i + 1));
	minishell->fake_env = (char **)ft_malloc(&minishell->global,
			sizeof(char *) * (i + 1));
	if (!minishell->env || !minishell->fake_env)
		ft_exit("Allocation error", 1, minishell);
	i = 0;
	while (env[i])
	{
		minishell->env[i] = ft_strdup(env[i], &minishell->global);
		minishell->fake_env[i] = ft_strdup(env[i], &minishell->global);
		if (!minishell->env[i] || !minishell->fake_env[i])
			ft_exit("Allocation error", 1, minishell);
		i++;
	}
	minishell->env[i] = NULL;
	minishell->fake_env[i] = NULL;
}

void	init_custom_env(t_minishell *minishell)
{
	char	*cwd;

	minishell->env = ft_malloc(&minishell->global, sizeof(char *) * 4);
	minishell->fake_env = ft_malloc(&minishell->global, sizeof(char *) * 4);
	if (!minishell->env || !minishell->fake_env)
		ft_exit("Allocation error", 1, minishell);
	(1) && (cwd = NULL, cwd = getcwd(NULL, 0));
	if (!cwd)
		ft_exit("getcwd failed", 1, minishell);
	minishell->env[0] = ft_strjoin("OLDPWD", "", &minishell->global);
	minishell->env[1] = ft_strjoin("PWD=", cwd, &minishell->global);
	minishell->env[2] = ft_strjoin("SHLVL=", "1", &minishell->global);
	minishell->env[3] = NULL;
	minishell->fake_env[0] = ft_strjoin("PWD=", cwd, &minishell->global);
	minishell->fake_env[1] = ft_strjoin("SHLVL=", "1", &minishell->global);
	minishell->fake_env[2] = ft_strjoin("_=", ft_strjoin(cwd, "/./minishell",
				&minishell->local), &minishell->global);
	minishell->fake_env[3] = NULL;
	free(cwd);
	if (!minishell->env[0] || !minishell->env[1] || !minishell->env[2]
		|| !minishell->fake_env[0] || !minishell->fake_env[1]
			|| !minishell->fake_env[2])
		ft_exit("Allocation error", 1, minishell);
}
