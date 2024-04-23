/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:31:01 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/22 08:22:20 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_sign(t_tokenizer **new, char *s, int *j, int *i)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
		(1) && (*j = 2, (*new)->type = DELIMITER);
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

	(1) && (j = 0, k = 0, new = malloc(sizeof(t_tokenizer)));
	if (!new)
	{
		free_tokens(t);
		ft_exit("Allocation error", 1, &m->garbage);
	}
	check_sign(&new, s, &j, i);
	new->token = malloc(j + 1);
	if (!new->token)
	{
		free(new);
		free_tokens(t);
		ft_exit("Allocation error", 1, &m->garbage);
	}
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

	(1) && (j = 1, k = 0, new = malloc(sizeof(t_tokenizer)));
	if (!new)
	{
		free_tokens(t);
		ft_exit("Allocation error", 1, &m->garbage);
	}
	while (s[*i + j] && s[*i + j] != '"')
		j++;
	if (s[*i + j] == '"')
		j++;
	(1) && (new->token = malloc(j + 1), new->type = D_QUOTE, new->next = NULL);
	if (!new->token)
	{
		free(new);
		free_tokens(t);
		ft_exit("Allocation error", 1, &m->garbage);
	}
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

	(1) && (j = 1, k = 0, new = malloc(sizeof(t_tokenizer)));
	if (!new)
	{
		free_tokens(t);
		ft_exit("Allocation error", 1, &m->garbage);
	}
	new->type = PARENTHESE;
	(1) && (new->next = NULL, new->token = malloc(j + 1));
	if (!new->token)
	{
		free(new);
		free_tokens(t);
		ft_exit("Allocation error", 1, &m->garbage);
	}
	while (k < j)
		(1) && (new->token[k] = s[*i], k++, (*i)++);
	(1) && ((*i)--, new->token[k] = '\0');
	add_token(t, new);
}
