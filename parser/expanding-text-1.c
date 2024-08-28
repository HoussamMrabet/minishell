/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding-text-1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:45:05 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/28 13:46:26 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_text_expand5(t_minishell *m, char **tok, char **str, int *i)
{
	int		j;

	j = 1;
	if ((*tok + (*i))[j] == '_' || ft_isal((*tok + (*i))[j]))
	{
		j++;
		while ((*tok + (*i))[j] == '_' || ft_isalnum((*tok + (*i))[j]))
			j++;
	}
	(1) && (j--, *str = ft_substr(m, ((*tok + (*i)) + 1), 0, j));
	(*i) += j;
	return (*str);
}
