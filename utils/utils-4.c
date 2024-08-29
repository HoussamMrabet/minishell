/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:41:01 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/29 14:17:31 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_readline(t_minishell *minishell, char *input, t_bool add)
{
	char	*res;
	char	*in;

	res = readline(input);
	if (!res)
		return (NULL);
	in = ft_strdup(res, minishell, &minishell->local);
	free(res);
	if (add && in && in[0])
		add_history(in);
	return (in);
}

void	*ft_getcwd(t_minishell *minishell)
{
	char	*cwd;
	char	*res;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	res = ft_strdup(cwd, minishell, &minishell->local);
	free(cwd);
	return (res);
}

void	close_fds(void)
{
	int	fd;

	fd = OPEN_MAX;
	while (fd >= 3)
	{
		close(fd);
		fd--;
	}
}

char	*ft_strtrim(t_minishell *mini, char *s1, char *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, *(s1 + start)) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1, mini, &mini->local));
	while (ft_strchr(set, *(s1 + end)) && end >= 0)
		end--;
	str = ft_malloc(mini, &mini->local, end - start + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 2);
	return (str);
}

void	reverse_str(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\002')
			(*str)[i] = ' ';
		i++;
	}
}
