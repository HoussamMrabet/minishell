/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:28:45 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/23 18:23:00 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quotes(t_minishell *s, t_tokenizer **t, char *n, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 1, k = 0, new = ft_malloc(&s->tmp, sizeof(t_tokenizer)));
	if (!new)
		ft_exit("Allocation error", 1, s);
	while (n[*i + j] && n[*i + j] != '\'')
		j++;
	if (n[*i + j] == '\'')
		j++;
	new->token = ft_malloc(&s->tmp, j + 1);
	if (!new->token)
		ft_exit("Allocation error", 1, s);
	(1) && (new->type = S_QUOTE, new->next = NULL);
	while (k < j)
		(1) && (new->token[k] = n[*i], k++, (*i)++);
	(1) && ((*i)--, new->token[k] = '\0');
	add_token(t, new);
}

void	handle_pipe_or_sign(t_minishell *m, t_tokenizer **t, char *s, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 0, k = 0, new = ft_malloc(&m->tmp, sizeof(t_tokenizer)));
	if (!new)
		ft_exit("Allocation error", 1, m);
	if (s[*i] == '|' && s[*i + 1] == '|')
		(1) && (j = 2, new->type = OR);
	else
		(1) && (j = 1, new->type = PIPE);
	(1) && (new->next = NULL, new->token = ft_malloc(&m->tmp, j + 1));
	if (!new->token)
		ft_exit("Allocation error", 1, m);
	while (k < j)
		(1) && (new->token[k] = s[*i], k++, (*i)++);
	(1) && ((*i)--, new->token[k] = '\0');
	add_token(t, new);
}

void	handle_and_sign(t_minishell *m, t_tokenizer **t, char *s, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 2, k = 0, new = ft_malloc(&m->tmp, sizeof(t_tokenizer)));
	if (!new)
		ft_exit("Allocation error", 1, m);
	new->token = ft_malloc(&m->tmp, j + 1);
	if (!new->token)
		ft_exit("Allocation error", 1, m);
	(1) && (new->type = AND, new->next = NULL);
	while (k < j)
		(1) && (new->token[k] = s[*i], k++, (*i)++);
	(1) && ((*i)--, new->token[k] = '\0');
	add_token(t, new);
}

void	handle_spaces(t_minishell *m, t_tokenizer **t, char *s, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 1, k = 0, new = ft_malloc(&m->tmp, sizeof(t_tokenizer)));
	if (!new)
		ft_exit("Allocation error", 1, m);
	while (s[*i + j] && (s[*i + j] == ' ' || s[*i + j] == '\t'))
		j++;
	new->token = ft_malloc(&m->tmp, j + 1);
	if (!new->token)
		ft_exit("Allocation error", 1, m);
	(1) && (new->type = SPACES, new->next = NULL);
	while (k < j)
		(1) && (new->token[k] = s[*i], k++, (*i)++);
	(1) && ((*i)--, new->token[k] = '\0');
	add_token(t, new);
}

void	handle_commands(t_minishell *m, t_tokenizer **t, char *s, int *i)
{
	t_tokenizer	*new;
	int			j[2];

	(1) && (j[0] = 0, j[1] = 0, new = ft_malloc(&m->tmp, sizeof(t_tokenizer)));
	if (!new)
		ft_exit("Allocation error", 1, m);
	while (s[*i + j[0]] && s[*i + j[0]] != '\'' && s[*i + j[0]] != '"'
		&& s[*i + j[0]] != ' ' && s[*i + j[0]] != '\t' && s[*i + j[0]] != '|'
		&& s[*i + j[0]] != '<' && s[*i + j[0]] != '>'
		&& s[*i + j[0]] != '(' && s[*i + j[0]] != ')')
		j[0]++;
	new->token = ft_malloc(&m->tmp, j[0] + 1);
	if (!new->token)
		ft_exit("Allocation error", 1, m);
	(1) && (new->type = TEXT, new->next = NULL);
	while (j[1] < j[0])
		(1) && (new->token[j[1]] = s[*i], j[1]++, (*i)++);
	(1) && ((*i)--, new->token[j[1]] = '\0');
	add_token(t, new);
}
