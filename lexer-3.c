/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:11:54 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/22 15:42:01 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	between_parenth(char *input, int *i);

static inline int	double_condition(char *input, int i)
{
	return ((input[i] == '<' && input[(i) + 1] == '<')
		|| (input[i] == '>' && input[(i) + 1] == '>')
		|| (input[i] == '|' && input[(i) + 1] == '|')
		|| (input[i] == '&' && input[(i) + 1] == '&'));
}

static int	between_parenth2(char *input, int *i)
{
	if (double_condition(input, *i))
	{
		*i += 2;
		while (input[*i] == ' ' || input[*i] == '\t')
			(*i)++;
		if (input[*i] == ')')
			return (1);
	}
	else if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
	{
		while (input[++(*i)] == ' ' || input[*i] == '\t')
			(*i)++;
		if (input[*i] == ')')
			return (1);
	}
	else if (input[*i] == '(')
	{
		(*i)++;
		if (between_parenth(input, i))
			return (1);
	}
	else
		(*i)++;
	return (0);
}

static int	between_parenth(char *input, int *i)
{
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
	if (input[*i] && (input[*i] == '|' || input[*i] == '&'))
		return (1);
	while (input[*i] && input[*i] != ')')
	{
		if (input[*i] == '\'')
		{
			while (input[++(*i)] && input[*i] != '\'')
				(*i)++;
			(*i)++;
		}
		else if (input[*i] == '"')
		{
			while (input[++(*i)] && input[*i] != '"')
				(*i)++;
			(*i)++;
		}
		else if (between_parenth2(input, i))
			return (1);
	}
	(*i)++;
	return (0);
}

static int	syntax_invalid2(char *input, int *i)
{
	if (double_condition(input, *i))
	{
		(*i) += 2;
		while (input[*i] == ' ' || input[*i] == '\t')
			i++;
		if (!input[*i])
			return (1);
	}
	else if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
	{
		while (input[++(*i)] == ' ' || input[*i] == '\t')
			(*i)++;
		if (!input[*i])
			return (1);
	}
	else if (input[*i] == '(')
	{
		(*i)++;
		if (between_parenth(input, i))
			return (1);
	}
	else
		(*i)++;
	return (0);
}

int	syntax_invalid(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] && (input[i] == '|' || input[i] == '&'))
		return (1);
	while (input[i])
	{
		if (input[i] == '\'')
		{
			while (input[++i] && input[i] != '\'')
				i++;
			i++;
		}
		else if (input[i] == '"')
		{
			while (input[++i] && input[i] != '"')
				i++;
			i++;
		}
		else if (syntax_invalid2(input, &i))
			return (1);
	}
	return (0);
}
