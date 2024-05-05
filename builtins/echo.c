/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:46:12 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/05 17:40:55 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_echo(t_minishell *minishell, char *cmd)
{
	char	**cmd_splited;
	char	*res;
	int		i;
	t_bool	with_op;
	
	i = 1;
	with_op = FALSE;
	res = ft_strdup("", &minishell->local);
	cmd_splited = ft_split(cmd, ' ', &minishell->local);
	if (ft_strcmp("-n", cmd_splited[i]))
	{
		with_op = TRUE;
		i++;
	}
	while (cmd_splited[i])
	{
		res = ft_strjoin(res, cmd_splited, &minishell->local);
		i++;
	}
	if (!with_op)
		res = ft_strjoin(res, "\n", &minishell->local);
}
