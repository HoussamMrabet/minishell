/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:56:47 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 05:33:21 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_io_token(t_exec **tree, t_iofiles *new)
{
	t_iofiles	*tmp;

	tmp = (*tree)->iofiles;
	if (!tmp)
		(*tree)->iofiles = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->next = NULL;
	}
}

static void	remove_unused_tokens2(t_tokenizer *token)
{
	t_tokenizer	*tmp;
	t_bool		b;

	while (token)
	{
		(1) && (b = FALSE, tmp = token->next);
		if (tmp && (tmp->type == DEL || tmp->type == APPEND
				|| tmp->type == IN_RED || tmp->type == OUT_RED))
		{
			tmp = tmp->next;
			(tmp && tmp->type == SPACES) && (tmp = tmp->next);
			while (tmp && (tmp->type == WILD_CARD || tmp->type == CMD
					|| tmp->type == TEXT || tmp->type == DELIM
					|| tmp->type == Q_DELIM || tmp->type == EXPAND
					|| tmp->type == S_QUOTE || tmp->type == Q_DELIM))
				tmp = tmp->next;
			(tmp && tmp->type == SPACES) && (tmp = tmp->next);
			(1) && (token->next = tmp, b = TRUE);
		}
		(!b) && (token = token->next);
	}
}

static void	remove_unused_tokens(t_exec **tree)
{
	t_tokenizer	*token;

	token = (*tree)->tokens;
	while (token && token->type == SPACES)
		token = token->next;
	(*tree)->tokens = token;
	while (token && (token->type == DEL || token->type == APPEND
			|| token->type == IN_RED || token->type == OUT_RED))
	{
		token = token->next;
		(token->type == SPACES) && (token = token->next);
		while (token && (token->type == WILD_CARD || token->type == CMD
				|| token->type == TEXT || token->type == DELIM
				|| token->type == Q_DELIM || token->type == EXPAND
				|| token->type == S_QUOTE || token->type == Q_DELIM))
			token = token->next;
		(token && token->type == SPACES) && (token = token->next);
		(*tree)->tokens = token;
	}
	remove_unused_tokens2(token);
}

static void	set_io_del_tokens(t_minishell *m, t_exec **tr,
		t_tokenizer *t, t_iofiles *io)
{
	char		*tp;

	tp = ft_strdup("", m, &m->local);
	io = ft_malloc(m, &m->local, sizeof(t_iofiles));
	io->type = t->type;
	io->amb = t->amb;
	io->next = NULL;
	tp = ft_strjoin(tp, t->token, m, &m->local);
	t = t->next;
	if (t && t->next && (t->next->type == DELIM
			|| t->next->type == Q_DELIM))
		t = t->next;
	(*tr)->fdin = ft_atoi(t->token);
	io->token = ft_strdup(tp, m, &m->local);
	add_io_token(tr, io);
}

void	set_io_tokens(t_minishell *m, t_exec **tr)
{
	t_tokenizer	*t;
	t_iofiles	*io;
	char		*r;

	t = (*tr)->tokens;
	while (t)
	{
		if (t->type == IN_RED || t->type == OUT_RED
			|| t->type == APPEND)
		{
			(1) && (r = ft_strdup("", m, &m->local), io = ft_malloc(m,
					&m->local, sizeof(t_iofiles)), io->type = t->type,
					io->next = NULL, t = t->next);
			(t && t->type == SPACES) && (t = t->next);
			(1) && (io->amb = TRUE, r = ft_strjoin(r, "", m, &m->local));
			t && (io->amb = t->amb, r = ft_strjoin(r, t->token, m, &m->local));
			(!r[0] || (t && t->type == SPACES)) && (io->amb = TRUE);
			io->token = ft_strdup(r, m, &m->local);
			add_io_token(tr, io);
		}
		else if (t->type == DEL)
			set_io_del_tokens(m, tr, t, io);
		(t) && (t = t->next);
	}
	remove_unused_tokens(tr);
}
