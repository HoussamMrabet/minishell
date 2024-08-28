/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding-quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:45:28 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/28 13:47:58 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote_expand4(t_minishell *m, char **tok, int *i, char	**v)
{
	int		j;
	char	*tmp;
	char	*str;

	j = 1;
	if ((*tok + (*i))[j] == '_' || ft_isal((*tok + (*i))[j]))
	{
		j++;
		while ((*tok + (*i))[j] == '_' || ft_isalnum((*tok + (*i))[j]))
			j++;
	}
	(1) && (j--, tmp = ft_substr(m, ((*tok + (*i)) + 1), 0, j));
	str = get_env_value(m, tmp);
	(!str) && (str = ft_strdup("", m, &m->local));
	(1) && (*v = ft_strjoin((*v), str, m, &m->local), (*i) += j);
}

static char	*handle_quote_expand3(t_minishell *m, char **tok, int *i)
{
	int		j;
	char	*str;

	j = 1;
	if ((*tok + (*i))[j] == '_' || ft_isal((*tok + (*i))[j]))
	{
		j++;
		while ((*tok + (*i))[j] == '_' || ft_isalnum((*tok + (*i))[j]))
			j++;
	}
	(1) && (j--, str = ft_substr(m, ((*tok + (*i)) + 1), 0, j));
	(*i) += j;
	return (str);
}

static void	handle_quote_expand2(t_minishell *m, char **tok, char **val, int *i)
{
	char	*tmp;

	if ((*tok)[(*i) + 1] == '?')
		(1) && (tmp = ft_itoa(m, &m->local, exit_status(0, FALSE)),
			*val = ft_strjoin((*val), tmp, m, &m->local), (*i)++);
	else if ((*tok)[(*i) + 1] == '_' && !(*tok)[(*i) + 2])
		(1) && (*val = ft_strjoin((*val), m->_, m, &m->local), (*i)++);
	else if ((*tok)[(*i) + 1] == '"' || (!ft_isalnum((*tok)[(*i) + 1])
			&& (*tok)[(*i) + 1] != '_'))
		(*val) = ft_strjoin((*val), "$", m, &m->local);
	else if ((*tok)[(*i) + 1] >= '0' && (*tok)[(*i) + 1] <= '9')
	{
		*i += 1;
		*val = ft_strjoin((*val), handle_quote_expand3(m, tok, i),
				m, &m->local);
	}
	else
		handle_quote_expand4(m, tok, i, val);
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
