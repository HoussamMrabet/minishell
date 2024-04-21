/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:28:45 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/21 17:29:32 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quotes(t_minishell *s, t_tokenizer **t, char *n, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 1, k = 0, new = malloc(sizeof(t_tokenizer)));
	if (!new)
	{
		free_tokens(t);
		ft_exit("Allocation error", 1, &s->garbage);
	}
	while (n[*i + j] && n[*i + j] != '\'')
		j++;
	if (n[*i + j] == '\'')
		j++;
	(1) && (new->token = malloc(j + 1), new->type = S_QUOTE, new->next = NULL);
	if (!new->token)
	{
		free(new);
		free_tokens(t);
		ft_exit("Allocation error", 1, &s->garbage);
	}
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

	(1) && (j = 0, k = 0, new = malloc(sizeof(t_tokenizer)));
	if (!new)
	{
		free_tokens(t);
		ft_exit("Allocation error", 1, &m->garbage);
	}
	if (s[*i] == '|' && s[*i + 1] == '|')
		(1) && (j = 2, new->type = OR);
	else
		(1) && (j = 1, new->type = PIPE);
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

void	handle_and_sign(t_minishell *m, t_tokenizer **t, char *s, int *i)
{
	t_tokenizer	*new;
	int			j;
	int			k;

	(1) && (j = 2, k = 0, new = malloc(sizeof(t_tokenizer)));
	if (!new)
	{
		free_tokens(t);
		ft_exit("Allocation error", 1, &m->garbage);
	}
	(1) && (new->type = AND, new->next = NULL, new->token = malloc(j + 1));
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

void	handle_spaces(t_minishell *m, t_tokenizer **t, char *s, int *i)
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
	while (s[*i + j] && (s[*i + j] == ' ' || s[*i + j] == '\t'))
		j++;
	(1) && (new->type = SPACES, new->next = NULL, new->token = malloc(j + 1));
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

void	handle_commands(t_minishell *m, t_tokenizer **t, char *s, int *i)
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
	while (s[*i + j] && s[*i + j] != '\'' && s[*i + j] != '"'
		&& s[*i + j] != ' ' && s[*i + j] != '\t' && s[*i + j] != '|'
		&& s[*i + j] != '<' && s[*i + j] != '>' && s[*i + j] != '&')
		j++;
	(1) && (new->type = TEXT, new->next = NULL, new->token = malloc(j + 1));
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