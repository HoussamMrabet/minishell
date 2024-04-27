/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 06:46:42 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/27 12:07:26 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	ft_isalnum(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}
