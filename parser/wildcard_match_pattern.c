/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match_pattern.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:38:56 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/24 10:12:08 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	file_match2(t_bool **dp, char *pattern, char *filename)
{
	int	i;
	int	j;
	int	m;
	int	n;

	1 && (m = ft_strlen(pattern), n = ft_strlen(filename), i = 1);
	while (i <= m)
	{
		j = 1;
		while (j <= n)
		{
			if (pattern[i - 1] == filename[j - 1] || pattern[i - 1] == '*')
			{
				if (pattern[i - 1] == '*')
					dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]);
				else
					dp[i][j] = dp[i - 1][j - 1];
			}
			else
				dp[i][j] = FALSE;
			j++;
		}
		i++;
	}
}

t_bool	file_match(t_minishell *mi, char *pattern, char *filename)
{
	int		m;
	int		n;
	int		i;
	t_bool	**dp;

	if (pattern[0] != '*' && pattern[0] != filename[0])
		return (FALSE);
	(1) && (m = ft_strlen(pattern), n = ft_strlen(filename), i = 0);
	dp = ft_malloc(mi, &mi->local, (m + 1) * sizeof(t_bool *));
	while (i <= m)
		1 && (dp[i] = ft_malloc(mi, &mi->local, (n + 1) * sizeof(t_bool)), i++);
	i = 0;
	while (i <= m)
	{
		dp[i][0] = (i == 0) || (pattern[i - 1] == '*' && dp[i - 1][0]);
		i++;
	}
	dp[0][0] = TRUE;
	file_match2(dp, pattern, filename);
	return (dp[m][n]);
}
