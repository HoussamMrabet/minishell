/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 08:10:38 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/24 09:34:49 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(t_block_memory **g, char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		res = (char *)ft_malloc(g, 1);
		if (!res)
			return (NULL);
		return (res[0] = '\0', res);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	res = (char *)ft_malloc(g, sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && *(s + start + i))
	{
		*(res + i) = *(s + start + i);
		i++;
	}
	return (*(res + i) = '\0', res);
}

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	if (!arr[0])
		return (0);
	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

t_bool	is_equal(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (*(str + i) && (*(str + i) == ' '
			|| (*(str + i) >= 9 && *(str + i) <= 13)))
		i++;
	if (*(str + i) == '+' || *(str + i) == '-')
	{
		if (*(str + i) == '-')
			sign = -sign;
		i++;
	}
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		res = res * 10 + *(str + i) - 48;
		i++;
	}
	return (sign * (int)res);
}

void	ft_exit(char *msg, int status, t_minishell *minishell)
{
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 1);
	}
	ft_free(&minishell->global);
	ft_free(&minishell->local);
	exit(status);
}
