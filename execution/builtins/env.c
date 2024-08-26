/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:52:06 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 16:47:59 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *m, t_exec *tree)
{
	char	*res;
	int		i;

	exit_status(0, TRUE);
	open_files(m, tree);
	i = 0;
	res = ft_strdup("", m, &m->local);
	while (m->fake_env[i])
	{
		res = ft_strjoin(res, m->fake_env[i], m, &m->local);
		res = ft_strjoin(res, "\n", m, &m->local);
		i++;
	}
	i = 0;
	ft_putstr_fd(res, tree->fdout);
}
