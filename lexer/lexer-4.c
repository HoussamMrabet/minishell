/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:08:04 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 18:57:00 by hmrabet          ###   ########.fr       */
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

static int	between_parenth3(t_minishell *m, int *i, char *input)
{
	int	k;

	k = *i;
	*i += 2;
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
	if (input[*i] == ')')
		return (m->err.msg = ft_strjoin(SYNTAX_MSG"`", ft_strjoin(
					ft_substr(m, input + k, 0, 2), "'\n", m,
					&m->local), m, &m->local), m->err.pos = *i, 1);
	else
		return (0);
}

static int	between_parenth2(t_minishell *m, char *input, int *i)
{
	int	k;

	k = 0;
	if (check_signs(input, *i))
		return (between_parenth3(m, i, input));
	else if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
	{
		k = *i;
		(*i)++;
		while (input[*i] == ' ' || input[*i] == '\t')
			(*i)++;
		if (input[*i] == ')')
			return (m->err.msg = ft_strjoin(SYNTAX_MSG"`", ft_strjoin(
						ft_substr(m, input + k, 0, 1), "'\n", m,
						&m->local), m, &m->local), m->err.pos = *i, 1);
	}
	else if (input[*i] == '(')
	{
		(*i)++;
		if (between_parenth(m, input, i))
			return (1);
	}
	else
		(*i)++;
	return (0);
}

static int	between_parenth1(t_minishell *m, char *input, int *i)
{
	while (input[*i] && input[*i] != ')')
	{
		if (input[*i] == '\'')
		{
			(*i)++;
			while (input[*i] && input[*i] != '\'')
				(*i)++;
			(*i)++;
		}
		else if (input[*i] == '"')
		{
			(*i)++;
			while (input[*i] && input[*i] != '"')
				(*i)++;
			(*i)++;
		}
		else if (between_parenth2(m, input, i))
			return (1);
	}
	return (0);
}

int	between_parenth(t_minishell *m, char *input, int *i)
{
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
	if (input[*i] && (input[*i] == '|' || input[*i] == '&'))
	{
		if (input[(*i) + 1] == '|' || input[(*i) + 1] == '&')
			m->err.msg = ft_strjoin(SYNTAX_MSG"`", ft_strjoin(ft_substr(m,
							input + (*i), 0, 2), "'\n", m,
						&m->local), m, &m->local);
		else
			m->err.msg = ft_strjoin(SYNTAX_MSG"`", ft_strjoin(ft_substr(m,
							input + (*i), 0, 1), "'\n", m,
						&m->local), m, &m->local);
		return (m->err.pos = *i, 1);
	}
	if (between_parenth1(m, input, i))
		return (1);
	(*i)++;
	return (0);
}
