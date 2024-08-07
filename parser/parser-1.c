/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:30:17 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/08 18:57:00 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	merge_delimiters2(t_minishell *m, t_tokenizer **tmp,
		t_tokenizer **t, char **str)
{
	int	i;

	while (*tmp && (*tmp)->type != SPACES)
	{
		if ((*tmp)->type == S_QUOTE || (*tmp)->type == D_QUOTE)
		{
			i = 1;
			while (((*tmp)->type == S_QUOTE && (*tmp)->token[i] != '\'')
				|| ((*tmp)->type == D_QUOTE && (*tmp)->token[i] != '"'))
				i++;
			if (!(i == 1))
				*str = ft_strjoin(*str, ft_substr(m,
							(*tmp)->token + 1, 0, i - 1), m, &m->local);
			(*t)->type = Q_DELIM;
		}
		else if ((*tmp)->type == TEXT || (*tmp)->type == WILD_CARD)
			*str = ft_strjoin(*str, (*tmp)->token, m, &m->local);
		else
			break ;
		*tmp = (*tmp)->next;
	}
}

void	merge_delimiters(t_minishell *m, t_tokenizer **tokens)
{
	t_tokenizer	*t;
	t_tokenizer	*tmp;
	char		*str;

	t = *tokens;
	while (t)
	{
		if (t->type == DEL)
		{
			t = t->next;
			if (t->type == SPACES)
				t = t->next;
			(1) && (str = ft_strdup("", m, &m->local), tmp = t);
			merge_delimiters2(m, &tmp, &t, &str);
			(t->type == TEXT || t->type == WILD_CARD) && (t->type = DELIM);
			(1) && (t->token = str, t->next = tmp);
		}
		t = t->next;
	}
}
