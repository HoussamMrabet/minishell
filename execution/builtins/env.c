/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:52:06 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/09 14:32:42 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env(t_minishell *minishell)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("", &minishell->local);
	if (!res)
		ft_exit("Allocation error", 1, minishell);
	while (minishell->env[i])
	{
		res = ft_strjoin(res, minishell->env[i], &minishell->local);
		if (!res)
			ft_exit("Allocation error", 1, minishell);
		res = ft_strjoin(res, "\n", &minishell->local);
		if (!res)
			ft_exit("Allocation error", 1, minishell);
		i++;
	}
	i = 0;
	while (minishell->env[i])
	{
		printf("%s\n", minishell->env[i]);
		i++;
	}
	return (res);
}
