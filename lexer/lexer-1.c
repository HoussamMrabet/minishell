/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:28:45 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/25 04:46:34 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quotes(t_minishell *s, t_tokenizer **t, char *n, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 1, k = 0, new = ft_malloc(s, &s->local, sizeof(t_tokenizer)));
	while (n[*i + j] && n[*i + j] != '\'')
		j++;
	if (n[*i + j] == '\'')
		j++;
	new->token = ft_malloc(s, &s->local, j + 1);
	(1) && (new->type = S_QUOTE, new->next = NULL);
	new->amb = FALSE;
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

	(1) && (j = 0, k = 0, new = ft_malloc(m, &m->local, sizeof(t_tokenizer)));
	if (s[*i] == '|' && s[*i + 1] == '|')
		(1) && (j = 2, new->type = OR);
	else
		(1) && (j = 1, new->type = PIPE);
	new->amb = FALSE;
	(1) && (new->next = NULL, new->token = ft_malloc(m, &m->local, j + 1));
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

	(1) && (j = 2, k = 0, new = ft_malloc(m, &m->local, sizeof(t_tokenizer)));
	new->token = ft_malloc(m, &m->local, j + 1);
	(1) && (new->type = AND, new->amb = FALSE, new->next = NULL);
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

	(1) && (j = 1, k = 0, new = ft_malloc(m, &m->local, sizeof(t_tokenizer)));
	while (s[*i + j] && (s[*i + j] == ' ' || s[*i + j] == '\t'))
		j++;
	new->token = ft_malloc(m, &m->local, j + 1);
	(1) && (new->type = SPACES, new->amb = FALSE, new->next = NULL);
	while (k < j)
		(1) && (new->token[k] = s[*i], k++, (*i)++);
	(1) && ((*i)--, new->token[k] = '\0');
	add_token(t, new);
}

void	handle_commands(t_minishell *m, t_tokenizer **t, char *s, int *i)
{
	t_tokenizer	*new;
	int			j[2];

	(1) && (j[0] = 0, j[1] = 0);
	new = ft_malloc(m, &m->local, sizeof(t_tokenizer));
	while (s[*i + j[0]] && s[*i + j[0]] != '\'' && s[*i + j[0]] != '"'
		&& s[*i + j[0]] != ' ' && s[*i + j[0]] != '\t' && s[*i + j[0]] != '|'
		&& s[*i + j[0]] != '<' && s[*i + j[0]] != '>' && s[*i + j[0]] != '&'
		&& s[*i + j[0]] != '(' && s[*i + j[0]] != ')')
		j[0]++;
	new->token = ft_malloc(m, &m->local, j[0] + 1);
	(1) && (new->type = TEXT, new->amb = FALSE, new->next = NULL);
	while (j[1] < j[0])
		(1) && (new->token[j[1]] = s[*i], j[1]++, (*i)++);
	(1) && ((*i)--, new->token[j[1]] = '\0');
	add_token(t, new);
}
