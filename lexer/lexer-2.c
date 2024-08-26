/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:31:01 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 04:46:43 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_sign(t_tokenizer **new, char *s, int *j, int *i)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
		(1) && (*j = 2, (*new)->type = DEL);
	else if (s[*i] == '>' && s[*i + 1] == '>')
		(1) && (*j = 2, (*new)->type = APPEND);
	else if (s[*i] == '>')
		(1) && (*j = 1, (*new)->type = OUT_RED);
	else
		(1) && (*j = 1, (*new)->type = IN_RED);
}

void	handle_red_and_del(t_minishell *m, t_tokenizer **t, char *s, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 0, k = 0, new = ft_malloc(m, &m->local, sizeof(t_tokenizer)));
	check_sign(&new, s, &j, i);
	new->token = ft_malloc(m, &m->local, j + 1);
	new->amb = FALSE;
	new->next = NULL;
	while (k < j)
		(1) && (new->token[k] = s[*i], k++, (*i)++);
	(1) && ((*i)--, new->token[k] = '\0');
	add_token(t, new);
}

void	handle_double_quotes(t_minishell *m, t_tokenizer **t, char *s, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 1, k = 0, new = ft_malloc(m, &m->local, sizeof(t_tokenizer)));
	while (s[*i + j] && s[*i + j] != '"')
		j++;
	if (s[*i + j] == '"')
		j++;
	new->amb = FALSE;
	new->token = ft_malloc(m, &m->local, j + 1);
	(1) && (new->type = D_QUOTE, new->next = NULL);
	while (k < j)
		(1) && (new->token[k] = s[*i], k++, (*i)++);
	(1) && ((*i)--, new->token[k] = '\0');
	add_token(t, new);
}

void	handle_paranthese(t_minishell *m, t_tokenizer **t, char *s, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 1, k = 0, new = ft_malloc(m, &m->local, sizeof(t_tokenizer)));
	new->type = PAR;
	new->amb = FALSE;
	(1) && (new->next = NULL, new->token = ft_malloc(m, &m->local, j + 1));
	while (k < j)
		(1) && (new->token[k] = s[*i], k++, (*i)++);
	(1) && ((*i)--, new->token[k] = '\0');
	add_token(t, new);
}
