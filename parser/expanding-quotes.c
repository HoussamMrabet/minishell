/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding-quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:45:28 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 06:28:32 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote_expand2(t_minishell *m, char **tok, char **val, int *i)
{
	int		j;
	char	*tmp[2];

	if ((*tok)[(*i) + 1] == '?')
		(1) && (tmp[1] = ft_itoa(m, &m->local, exit_status(0, FALSE)),
			*val = ft_strjoin((*val), tmp[1], m, &m->local), (*i)++);
	else if ((*tok)[(*i) + 1] == '_' && !(*tok)[(*i) + 2])
		(1) && (*val = ft_strjoin((*val), m->_, m, &m->local), (*i)++);
	else if ((*tok)[(*i) + 1] == '"' || (!ft_isalnum((*tok)[(*i) + 1])
			&& (*tok)[(*i) + 1] != '_'))
		(*val) = ft_strjoin((*val), "$", m, &m->local);
	else
	{
		j = 1;
		if ((*tok + (*i))[j] == '_' || ft_isal((*tok + (*i))[j]))
		{
			j++;
			while ((*tok + (*i))[j] == '_' || ft_isalnum((*tok + (*i))[j]))
				j++;
		}
		(1) && (j--, tmp[1] = ft_substr(m, ((*tok + (*i)) + 1), 0, j));
		tmp[0] = get_env_value(m, tmp[1]);
		(!tmp[0]) && (tmp[0] = ft_strdup("", m, &m->local));
		(1) && (*val = ft_strjoin((*val), tmp[0], m, &m->local), (*i) += j);
	}
}

void	handle_quote_expand(t_minishell *minishell, char **tokens)
{
	int			i;
	int			j;
	char		*tmp;
	char		*value;

	(1) && (i = 0, value = ft_strdup("", minishell, &minishell->local));
	while ((*tokens)[++i] != '"')
	{
		if ((*tokens)[i] == '$')
			handle_quote_expand2(minishell, tokens, &value, &i);
		else
		{
			j = 0;
			while (((*tokens) + i)[j] != '"' && ((*tokens) + i)[j] != '$')
				j++;
			tmp = ft_substr(minishell, (*tokens) + i, 0, j);
			value = ft_strjoin(value, tmp, minishell, &minishell->local);
			i += j - 1;
		}
	}
	*tokens = value;
}
