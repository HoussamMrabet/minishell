/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:46:12 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/11 19:31:48 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_echo(t_minishell *minishell, char *cmd)
{
	char	**cmd_splited;
	char	*res;
	int		i;
	t_bool	with_op;

	(1) && (i = 1, with_op = FALSE, res = ft_strdup("", &minishell->local));
	cmd_splited = ft_split(cmd, '\n', &minishell->local);
	if (!res || !cmd_splited)
		ft_exit("Allocation error", 1, minishell);
	if (cmd_splited[i])
	{
		(!ft_strcmp("-n", cmd_splited[i])) && (with_op = TRUE, i++);
		while (cmd_splited[i])
		{
			if (res[0])
				res = ft_strjoin(res, " ", &minishell->local);
			res = ft_strjoin(res, cmd_splited[i], &minishell->local);
			if (!res)
				ft_exit("Allocation error", 1, minishell);
			i++;
		}
	}
	(!with_op) && (res = ft_strjoin(res, "\n", &minishell->local));
	if (!res)
		ft_exit("Allocation error", 1, minishell);
	printf("%s", res);
	return (res);
}