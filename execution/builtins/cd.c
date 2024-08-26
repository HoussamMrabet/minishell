/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:54:30 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/26 17:47:17 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_values(t_exec *t, t_minishell *m, char *target, t_bool old)
{
	char	*cwd;

	(old) && (old = printf("%s\n", target));
	if (!t->is_pipe)
	{
		set_env_value(m, "OLDPWD", get_env_value(m, "PWD"));
		set_fake_env_value(m, "OLDPWD", get_env_value(m, "PWD"));
		cwd = ft_getcwd(m);
		if (!cwd)
		{
			set_env_value(m, "PWD", ft_strjoin(m->pwd, "/..", m, &m->local));
			set_fake_env_value(m, "PWD",
				ft_strjoin(m->pwd, "/..", m, &m->local));
			m->pwd = ft_strdup(ft_strjoin(m->pwd, "/..", m, &m->local),
					m, &m->global);
			ft_putstr_fd(CD_ERR_MSG1 CD_ERR_MSG2, 2);
		}
		else
		{
			set_env_value(m, "PWD", cwd);
			set_fake_env_value(m, "PWD", cwd);
			m->pwd = ft_strdup(cwd, m, &m->global);
		}
	}
	exit_status(0, TRUE);
}

static int	handle_dash(t_minishell *m, char **target, t_bool *oldpath)
{
	1 && (*target = get_env_value(m, "OLDPWD"), *oldpath = TRUE);
	if (!target || !*target || !*target[0])
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		exit_status(1, TRUE);
		return (1);
	}
	return (0);
}

void	ft_cd(t_minishell *m, t_exec *tree)
{
	char		*target;
	t_bool		oldpath;
	t_tokenizer	*tok;

	if (open_files_builtin(tree))
		return ;
	(1) && (tok = tree->tokens, tok = tok->next, oldpath = FALSE);
	(tok && tok->type == SPACES) && (tok = tok->next);
	if (!tok)
		target = m->home;
	else if (!ft_strcmp(tok->token, "-"))
	{
		if (handle_dash(m, &target, &oldpath))
			return ;
	}
	else
		target = ft_strdup(tok->token, m, &m->local);
	if (!tree->is_pipe && chdir(target))
	{
		exit_status(1, TRUE);
		perror("minishell: cd");
	}
	else
		change_values(tree, m, target, oldpath);
}
