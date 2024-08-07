/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:46:12 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 18:47:28 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_minishell *m, char *cmd)
{
	char	**cmd_splited;
	char	*res;
	int		i;
	t_bool	with_op;

	(1) && (i = 1, with_op = FALSE, res = ft_strdup("", m, &m->local));
	cmd_splited = ft_split_local(cmd, '\n', m);
	if (cmd_splited[i])
	{
		(!ft_strcmp("-n", cmd_splited[i])) && (with_op = TRUE, i++);
		while (cmd_splited[i])
		{
			(res[0]) && (res = ft_strjoin(res, " ", m, &m->local));
			res = ft_strjoin(res, cmd_splited[i], m, &m->local);
			i++;
		}
	}
	(!with_op) && (res = ft_strjoin(res, "\n", m, &m->local));
	ft_putstr_fd(res, 1);
}
