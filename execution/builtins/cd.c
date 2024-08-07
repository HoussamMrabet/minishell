/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:54:30 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 19:16:35 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_values(t_minishell *minishell, char *target, t_bool oldpath)
{
	char	*cwd;

	if (oldpath)
		printf("%s\n", target);
	set_env_value(minishell, "OLDPWD", get_env_value(minishell, "PWD"));
	set_fake_env_value(minishell, "OLDPWD", get_env_value(minishell, "PWD"));
	cwd = getcwd(NULL, 0);
	set_env_value(minishell, "PWD", cwd);
	set_fake_env_value(minishell, "PWD", cwd);
	free(cwd);
	exit_status(0, TRUE);
}

void	ft_cd(t_minishell *m, char *cmd)
{
	char	**splited;
	char	*target;
	t_bool	oldpath;

	(1) && (oldpath = FALSE, splited = ft_split_local(cmd, '\n', m));
	(1) && (((!splited[1]) && (target = "~")) || (target = splited[1]));
	(target[0] == '~') && (cmd = getenv("HOME"),
			target = ft_strjoin(cmd, target + 1, m, &m->local));
	if (!ft_strcmp(target, "-"))
	{
		(1) && (oldpath = TRUE, target = get_env_value(m, "OLDPWD"));
		if (!target[0])
		{
			printf("minishell: cd: OLDPWD not set\n");
			exit_status(1, TRUE);
			return ;
		}
	}
	if (chdir(target))
	{
		exit_status(1, TRUE);
		perror("minishell: cd");
	}
	else
		change_values(m, target, oldpath);
}
