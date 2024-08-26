/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:39:02 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/15 10:32:31 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirections_syntax(t_minishell *m, t_tokenizer **t, int *pos)
{
	*pos += ft_strlen((*t)->token);
	if ((*t)->next && (*t)->next->type == SPACES)
		(1) && (*t = (*t)->next, *pos += ft_strlen((*t)->token));
	if ((*t)->next && ((*t)->next->type == PIPE || (*t)->next->type == OR
			|| (*t)->next->type == AND || (*t)->next->type == IN_RED
			|| (*t)->next->type == OUT_RED || (*t)->next->type == DEL
			|| (*t)->next->type == APPEND))
		return (m->err.pos = *pos, m->err.msg = ft_strjoin(SYNTAX_MSG"`",
				ft_strjoin((*t)->next->token, "'\n", m, &m->local), m,
				&m->local), 1);
	return (0);
}

static int	check_operators_syntax(t_minishell *m, t_tokenizer **t, int *pos)
{
	if ((*t)->type == PIPE || (*t)->type == OR || (*t)->type == AND)
	{
		*pos += ft_strlen((*t)->token);
		if ((*t)->next && (*t)->next->type == SPACES)
			(1) && (*t = (*t)->next, *pos += ft_strlen((*t)->token));
		if ((*t)->next && ((*t)->next->type == PIPE || (*t)->next->type == OR
				|| (*t)->next->type == AND))
			return (m->err.pos = *pos, m->err.msg = ft_strjoin(SYNTAX_MSG"`",
					ft_strjoin((*t)->next->token, "'\n", m, &m->local), m,
					&m->local), 1);
	}
	else if ((*t)->type == IN_RED || (*t)->type == OUT_RED
		|| (*t)->type == DEL || (*t)->type == APPEND)
	{
		if (check_redirections_syntax(m, t, pos))
			return (1);
	}
	return (0);
}

static int	check_parenthese_syntax2(t_minishell *m, t_tokenizer **t, int *pos)
{
	if ((*t)->next && (*t)->next->type == SPACES)
		(1) && (*t = (*t)->next, *pos += ft_strlen((*t)->token));
	if ((*t)->next && (*t)->next->type == PAR && (*t)->next->token[0] == '('
		&& !((*t)->type == PAR && (*t)->token[0] == '('))
		return (m->err.pos = *pos, m->err.msg = ft_strjoin(SYNTAX_MSG"`",
				ft_strjoin((*t)->next->token, "'\n", m, &m->local),
				m, &m->local), 1);
	return (0);
}

static int	check_parenthese_syntax(t_minishell *m, t_tokenizer **t, int *pos)
{
	if ((*t)->next && (*t)->next->type == SPACES)
		(1) && (*t = (*t)->next, *pos += ft_strlen((*t)->token));
	while ((*t)->next && ((*t)->next->type == IN_RED
			|| (*t)->next->type == OUT_RED
			|| (*t)->next->type == APPEND || (*t)->next->type == DEL))
	{
		*t = (*t)->next;
		*pos += ft_strlen((*t)->token);
		if ((*t)->next && (*t)->next->type == SPACES)
			(1) && ((*t) = (*t)->next, *pos += ft_strlen((*t)->token));
		while ((*t)->next && ((*t)->next->type == TEXT
				|| (*t)->next->type == D_QUOTE || (*t)->next->type == S_QUOTE))
			(1) && (*t = (*t)->next, *pos += ft_strlen((*t)->token));
		*pos += ft_strlen((*t)->token);
		if ((*t)->next && (*t)->next->type == SPACES)
			(1) && ((*t) = (*t)->next, *pos += ft_strlen((*t)->token));
	}
	if ((*t)->next && !((*t)->next->type == PIPE || (*t)->next->type == OR
			|| (*t)->next->type == AND || ((*t)->next->type == PAR
				&& (*t)->next->token[0] == ')')))
		return (m->err.pos = *pos, m->err.msg = ft_strjoin(SYNTAX_MSG"`",
				ft_strjoin((*t)->next->token, "'\n", m, &m->local),
				m, &m->local), 1);
	return (0);
}

int	check_op_syntax(t_minishell *m)
{
	t_tokenizer	*t;
	int			pos;

	(1) && (t = m->tokens, pos = 0);
	while (t)
	{
		if (check_operators_syntax(m, &t, &pos))
			return (1);
		else if (t->type == PAR && t->token[0] == ')')
		{
			if (check_parenthese_syntax(m, &t, &pos))
				return (1);
		}
		else if (!(t->type == PIPE || t->type == OR
				|| t->type == AND || t->type == SPACES))
		{
			if (check_parenthese_syntax2(m, &t, &pos))
				return (1);
		}
		(1) && (pos += ft_strlen(t->token), t = t->next);
	}
	return (0);
}
