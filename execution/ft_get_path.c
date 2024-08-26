/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:52:31 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/08/25 16:11:47 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(t_minishell *mini, t_tokenizer *tokens)
{
	int		i;
	char	*test;

	i = 0;
	if (!ft_strncmp(tokens->token, "./", 2))
		return (tokens->token);
	else if (!ft_strchr(tokens->token, '/')
		&& access(tokens->token, F_OK | X_OK) == 0)
	{
		if (!mini->paths)
			return (tokens->token);
		return (NULL);
	}
	while (mini->paths && mini->paths[i])
	{
		test = ft_strjoin(mini->paths[i], tokens->token, mini, &mini->local);
		if (access(test, F_OK | X_OK) == 0)
			return (test);
		i++;
	}
	if (access(tokens->token, F_OK | X_OK) == 0)
		return (tokens->token);
	if (access(test, F_OK | X_OK) == 0)
		return (test);
	return (NULL);
}
