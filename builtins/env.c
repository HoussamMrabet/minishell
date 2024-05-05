/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:52:06 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/05 17:55:28 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env(t_minishell *minishell)
{
	char	*res;
	int		i;
	
	i = 0;
	res = ft_strdup("", &minishell->local);
	while (minishell->env[i])
	{
		res = ft_strjoin(res, minishell->env[i], &minishell->local);
		res = ft_strjoin(res, "\n", &minishell->local);
		i++;
	}
	return (res);
}
