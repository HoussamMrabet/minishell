/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:57:01 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/15 11:46:31 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_minishell *minishell, char *str)
{
	size_t	i;
	size_t	j;
	char	*var;
	char	**env;

	(1) && (env = minishell->env, i = -1);
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		var = ft_substr(minishell, env[i], 0, j);
		if (is_equal(str, var) && ft_strlen(str) == j)
		{
			var = ft_substr(minishell, env[i], j + 1,
					ft_strlen(env[i]) - j);
			return (var);
		}
	}
	return (ft_strdup("", minishell, &minishell->local));
}
