/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 08:10:55 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/12 12:28:00 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	starts_with(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && (!s2[i] || s2[i] == '='))
		return (i + 1);
	return (0);
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	int		size;
	char	*temp;

	i = 0;
	j = 0;
	size = 0;
	while (env[size])
		size++;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
