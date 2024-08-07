/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:20:25 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/09 06:08:54 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_content(char *input, int i)
{
	t_bool	is_empty;

	is_empty = TRUE;
	while (input[++i])
	{
		if (input[i] == ')')
			break ;
		if (input[i] != ' ' && input[i] != '\t')
			is_empty = FALSE;
	}
	return (is_empty);
}

static void	set_err(t_minishell *m, int i[], t_bool q[], int pos)
{
	if (q[0] || q[1])
		m->err.msg = ft_strdup(SYNTAX_MSG"`newline'\n", m, &m->local);
	else if (i[0] > 0)
	{
		m->err.msg = ft_strdup(SYNTAX_MSG"`newline'\n", m, &m->local);
		m->err.pos = pos;
	}
	else if (i[0] < 0 || i[2])
		m->err.msg = ft_strdup(SYNTAX_MSG"`)'\n", m, &m->local);
}

static void	check_quotes(t_minishell *m, int i, t_bool *stat1, t_bool stat2)
{
	if (*stat1)
		*stat1 = FALSE;
	else if (!*stat1 && !stat2)
		(1) && (m->err.pos = i, *stat1 = TRUE);
}

t_bool	format_invalid(t_minishell *m, char *input)
{
	t_bool	q[2];
	int		i[3];
	int		pos;

	(1) && (pos = 0, i[2] = 0, q[0] = FALSE, q[1] = FALSE, i[0] = 0, i[1] = -1);
	while (input[++i[1]])
	{
		if (input[i[1]] == '\'')
			check_quotes(m, i[1], &q[0], q[1]);
		else if (input[i[1]] == '"')
			check_quotes(m, i[1], &q[1], q[0]);
		if (input[i[1]] == '(' && !q[0] && !q[1])
		{
			(1) && (i[0]++, i[2] = check_content(input, i[1]));
			(!i[0]) && (pos = i[1]);
		}
		(input[i[1]] == ')' && !q[0] && !q[1]) && (i[0]--);
		if (i[0] < 0)
		{
			m->err.pos = i[1];
			break ;
		}
	}
	set_err(m, i, q, pos);
	return (q[0] || q[1] || i[0] || i[2]);
}
