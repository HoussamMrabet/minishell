/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:11:54 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/26 18:00:57 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	check_signs(char *input, int i)
{
	return ((input[i] == '<' && input[i + 1] == '<')
		|| (input[i] == '>' && input[i + 1] == '>')
		|| (input[i] == '|' && input[i + 1] == '|')
		|| (input[i] == '&' && input[i + 1] == '&'));
}

static int	syntax_invalid3(t_minishell *m, char *input, int *i)
{
	if (check_signs(input, *i))
	{
		m->err.pos = *i;
		*i += 2;
		while (input[*i] == ' ' || input[*i] == '\t')
			(*i)++;
		if (!input[*i])
			return (m->err.msg = ft_strdup(SYNTAX_MSG"`newline'\n",
					m, &m->local), 1);
	}
	return (0);
}

static int	syntax_invalid2(t_minishell *m, char *input, int *i)
{
	if (syntax_invalid3(m, input, i))
		return (1);
	else if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
	{
		(*i)++;
		while (input[*i] == ' ' || input[*i] == '\t')
			(*i)++;
		if (!input[*i])
			return (m->err.msg = ft_strdup(SYNTAX_MSG"`newlines'\n",
					m, &m->local), 1);
	}
	else if (input[*i] == '(' || input[*i] == '|' || input[*i] == '&')
	{
		(*i)++;
		if (between_parenth(m, input, i))
			return (1);
	}
	else
		(*i)++;
	return (0);
}

static int	syntax_invalid1(t_minishell *m, char *input, int *i)
{
	while (input[*i])
	{
		if (input[*i] == '\'')
		{
			(*i)++;
			while (input[*i] && input[(*i)++] != '\'')
				;
		}
		else if (input[*i] == '"')
		{
			(*i)++;
			while (input[*i] && input[(*i)++] != '"')
				;
		}
		else if (input[*i] == '&' && input[*i + 1] != '&')
			return (m->err.msg = ft_strjoin(SYNTAX_MSG"`", ft_strjoin(ft_substr(
							m, input + *i, 0, 2), "'\n", m, &m->local),
					m, &m->local), 1);
		else if (syntax_invalid2(m, input, i))
			return (1);
	}
	return (0);
}

int	syntax_invalid(t_minishell *m, char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] && (input[i] == '|' || input[i] == '&'))
	{
		while (input[i + 1] && (input[i + 1] == ' ' || input[i + 1] == '\t'))
			i++;
		if (input[i + 1] == '|' || input[i + 1] == '&')
			m->err.msg = ft_strjoin(SYNTAX_MSG"`", ft_strjoin(ft_substr(m,
							input + i, 0, 2), "'\n", m, &m->local),
					m, &m->local);
		else
			m->err.msg = ft_strjoin(SYNTAX_MSG"`", ft_strjoin(ft_substr(m,
							input + i, 0, 1), "'\n", m, &m->local),
					m, &m->local);
		return (m->err.pos = i, 1);
	}
	if (syntax_invalid1(m, input, &i))
		return (m->err.pos = i, 1);
	return (0);
}
