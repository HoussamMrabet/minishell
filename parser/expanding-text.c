/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding-text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:45:53 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/27 07:20:01 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_text_expand3(t_minishell *m, char **tok, char **str, int *i)
{
	int		j;
	char	*tmp;

	j = 1;
	if ((*tok + (*i))[j] == '_' || ft_isal((*tok + (*i))[j]))
	{
		j++;
		while ((*tok + (*i))[j] == '_' || ft_isalnum((*tok + (*i))[j]))
			j++;
	}
	(1) && (j--, *str = ft_substr(m, ((*tok + (*i)) + 1), 0, j));
	tmp = get_env_value(m, *str);
	(!tmp) && (tmp = ft_strdup("", m, &m->local));
	(*i) += j;
	return (tmp);
}

static void	handle_text_expand2(t_minishell *m, char **tok, char **val, int *i)
{
	char	*str;

	if ((*tok)[(*i) + 1] == '?')
		(1) && (str = ft_itoa(m, &m->local, exit_status(0, FALSE)),
			*val = ft_strjoin((*val), str, m, &m->local), (*i)++);
	else if ((*tok)[(*i) + 1] == '_' && !(*tok)[(*i) + 2])
		(1) && (*val = ft_strjoin((*val), m->_, m, &m->local), (*i)++);
	else if ((*tok)[(*i) + 1] >= '0' && (*tok)[(*i) + 1] <= '9')
		(1) && (*val = ft_strjoin((*val), (*tok) + 2, m, &m->local)
				, (*i) += ft_strlen(*tok) - 1);
	else if (!(*tok)[(*i) + 1] || (!ft_isalnum((*tok)[(*i) + 1])
			&& (*tok)[(*i) + 1] != '_'))
		(*val) = ft_strjoin((*val), "", m, &m->local);
	else
		*val = ft_strjoin((*val), handle_text_expand3(m, tok, &str, i),
				m, &m->local);
}

static void	handle_text_expand4(t_minishell *m, char **tok, char **val, int *i)
{
	int	j;

	j = 0;
	while ((*tok + *i)[j] && (*tok + *i)[j] != '$')
		j++;
	(1) && (*val = ft_strjoin(*val, ft_substr(m, (*tok) + *i, 0, j),
			m, &m->local), *i += j - 1);
}

static void	replace_val(char **val)
{
	int	i;

	i = 0;
	while ((*val)[i])
	{
		if ((*val)[i] == ' ')
			(*val)[i] = '\002';
		i++;
	}
}

void	handle_text_expand(t_minishell *m, t_tokenizer *tok, char **tokens)
{
	int			i;
	char		*val;

	(1) && (i = 0, val = ft_strdup("", m, &m->local));
	while ((*tokens)[i])
	{
		if ((*tokens)[i] == '$')
		{
			if (!(*tokens)[i + 1] && (!tok->next || (tok->next
					&& tok->next->type != D_QUOTE && tok->next->type != TEXT
					&& tok->next->type != S_QUOTE)))
				val = ft_strjoin(val, "$", m, &m->local);
			else
			{
				handle_text_expand2(m, tokens, &val, &i);
				replace_val(&val);
				(tok && ft_strchr(val, '\002')) && (tok->amb = TRUE);
			}
			(tok) && (tok->is_expand = TRUE);
		}
		else
			handle_text_expand4(m, tokens, &val, &i);
		i++;
	}
	*tokens = val;
}
