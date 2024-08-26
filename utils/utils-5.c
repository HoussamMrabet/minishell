/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:56:04 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/24 17:46:37 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((*(s1 + i) || *(s2 + i)) && i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!*needle || (!len && !*needle))
		return ((char *)haystack);
	if (!len)
		return (NULL);
	res = (char *)haystack;
	i = 0;
	if (len > ft_strlen(haystack))
		len = ft_strlen(haystack);
	if (*needle == '\0')
		return (res);
	while (i < len)
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j) && (i + j) < len)
		{
			if (needle[++j] == '\0')
				return (res + i);
		}
		i++;
	}
	return (NULL);
}

t_atoul	ft_atoul(char *str)
{
	unsigned long long			i;
	unsigned long long			res;
	int							sign;

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
	return (sign * res);
}
