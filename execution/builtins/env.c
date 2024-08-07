/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:52:06 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 14:25:54 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env(t_minishell *mini)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("", mini, &mini->local);
	while (mini->fake_env[i])
	{
		res = ft_strjoin(res, mini->fake_env[i], mini, &mini->local);
		res = ft_strjoin(res, "\n", mini, &mini->local);
		i++;
	}
	i = 0;
	while (mini->fake_env[i])
	{
		printf("%s\n", mini->fake_env[i]);
		i++;
	}
	return (res);
}
