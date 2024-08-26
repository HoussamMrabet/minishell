/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 06:46:42 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/19 14:06:12 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_strchr(char *s, char c)
{
	size_t	i;

	if (!s)
		return (FALSE);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	ft_isal(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

t_bool	ft_isalnum(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while ((*(s1 + i) || *(s2 + i)))
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}

t_tokenizer	*token_dup(t_minishell *minishell, t_tokenizer *token)
{
	t_tokenizer	*res;

	res = ft_malloc(minishell, &minishell->local, sizeof(t_tokenizer));
	res->lvl = token->lvl;
	res->type = token->type;
	res->token = ft_strdup(token->token, minishell, &minishell->local);
	res->next = NULL;
	return (res);
}
