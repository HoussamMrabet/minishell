/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:31:22 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/21 13:14:55 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokenizer **tokens)
{
	t_tokenizer	*to_free;
	t_tokenizer	*to_hold;

	to_free = *tokens;
	while (to_free)
	{
		to_hold = to_free->next;
		free(to_free->token);
		free(to_free);
		to_free = to_hold;
	}
}



void	handle_single_quotes(t_minishell *minishell, t_tokenizer **tokens, char *input, int *i)
{
	t_tokenizer *new;
	t_tokenizer *tmp;
	int			j;
	int			k;
	
	j = 1;
	k = 0;
	tmp = *tokens;
	new = malloc(sizeof(t_tokenizer));
	if (!new)
	{
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	while (input[*i + j] && input[*i + j] != '\'')
		j++;
	if (input[*i + j] == '\'')
		j++;
	new->token = malloc(j + 1);
	if (!new->token)
	{
		free(new);
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	new->type = S_QUOTE;
	new->next = NULL;
	while (k < j)
	{
		new->token[k] = input[*i];
		k++;
		(*i)++;
	}
	(*i)--;
	new->token[k] = '\0';
	if (!tmp)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_double_quotes(t_minishell *minishell, t_tokenizer **tokens, char *input, int *i)
{
	t_tokenizer *new;
	t_tokenizer *tmp;
	int			j;
	int			k;
	
	j = 1;
	k = 0;
	tmp = *tokens;
	new = malloc(sizeof(t_tokenizer));
	if (!new)
	{
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	while (input[*i + j] && input[*i + j] != '"')
		j++;
	if (input[*i + j] == '"')
		j++;
	new->token = malloc(j + 1);
	if (!new->token)
	{
		free(new);
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	new->type = D_QUOTE;
	new->next = NULL;
	while (k < j)
	{
		new->token[k] = input[*i];
		k++;
		(*i)++;
	}
	(*i)--;
	new->token[k] = '\0';
	if (!tmp)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_red_and_del(t_minishell *minishell, t_tokenizer **tokens, char *input, int *i)
{
	t_tokenizer *new;
	t_tokenizer *tmp;
	int			j;
	int			k;
	
	j = 0;
	k = 0;
	tmp = *tokens;
	new = malloc(sizeof(t_tokenizer));
	if (!new)
	{
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	if (input[*i] == '<' && input[*i + 1] == '<')
		(1) && (j = 2, new->type = DELIMITER);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		(1) && (j = 2, new->type = APPEND);
	else if (input[*i] == '>')
		(1) && (j = 1, new->type = OUT_RED);
	else
		(1) && (j = 1, new->type = IN_RED);
	new->token = malloc(j + 1);
	if (!new->token)
	{
		free(new);
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	new->next = NULL;
	while (k < j)
	{
		new->token[k] = input[*i];
		k++;
		(*i)++;
	}
	(*i)--;
	new->token[k] = '\0';
	if (!tmp)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_pipe_or_sign(t_minishell *minishell, t_tokenizer **tokens, char *input, int *i)
{
	t_tokenizer *new;
	t_tokenizer *tmp;
	int			j;
	int			k;
	
	j = 0;
	k = 0;
	tmp = *tokens;
	new = malloc(sizeof(t_tokenizer));
	if (!new)
	{
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	if (input[*i] == '|' && input[*i + 1] == '|')
		(1) && (j = 2, new->type = OR);
	else
		(1) && (j = 1, new->type = PIPE);
	new->token = malloc(j + 1);
	if (!new->token)
	{
		free(new);
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	new->next = NULL;
	while (k < j)
	{
		new->token[k] = input[*i];
		k++;
		(*i)++;
	}
	(*i)--;
	new->token[k] = '\0';
	if (!tmp)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_and_sign(t_minishell *minishell, t_tokenizer **tokens, char *input, int *i)
{
	t_tokenizer *new;
	t_tokenizer *tmp;
	int			j;
	int			k;
	
	j = 2;
	k = 0;
	tmp = *tokens;
	new = malloc(sizeof(t_tokenizer));
	if (!new)
	{
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	new->token = malloc(j + 1);
	if (!new->token)
	{
		free(new);
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	new->type = AND;
	new->next = NULL;
	while (k < j)
	{
		new->token[k] = input[*i];
		k++;
		(*i)++;
	}
	(*i)--;
	new->token[k] = '\0';
	if (!tmp)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_spaces(t_minishell *minishell, t_tokenizer **tokens, char *input, int *i)
{
	t_tokenizer *new;
	t_tokenizer *tmp;
	int			j;
	int			k;
	
	j = 1;
	k = 0;
	tmp = *tokens;
	new = malloc(sizeof(t_tokenizer));
	if (!new)
	{
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	while (input[*i + j] && (input[*i + j] == ' ' || input[*i + j] == '\t'))
		j++;
	new->token = malloc(j + 1);
	if (!new->token)
	{
		free(new);
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	new->type = SPACES;
	new->next = NULL;
	while (k < j)
	{
		new->token[k] = input[*i];
		k++;
		(*i)++;
	}
	(*i)--;
	new->token[k] = '\0';
	if (!tmp)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_commands(t_minishell *minishell, t_tokenizer **tokens, char *input, int *i)
{
	t_tokenizer *new;
	t_tokenizer *tmp;
	int			j;
	int			k;
	
	j = 0;
	k = 0;
	tmp = *tokens;
	new = malloc(sizeof(t_tokenizer));
	if (!new)
	{
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	while (input[*i + j] && input[*i + j] != '\'' && input[*i + j] != '"' && input[*i + j] != ' ' && input[*i + j] != '\t' && input[*i + j] != '|' && input[*i + j] != '<' && input[*i + j] != '>' && input[*i + j] != '&')
		j++;
	new->token = malloc(j + 1);
	if (!new->token)
	{
		free(new);
		free_tokens(tokens);
		ft_exit("Allocation error", 1, &minishell->garbage);
	}
	new->type = TEXT;
	new->next = NULL;
	while (k < j)
	{
		new->token[k] = input[*i];
		k++;
		(*i)++;
	}
	(*i)--;
	new->token[k] = '\0';
	if (!tmp)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}


void	lexer(t_minishell *minishell, char *input)
{
	int			i;
	t_tokenizer *tokens;
	t_tokenizer *tmp;

	i = 0;
	tokens = NULL;
	minishell->tokens = tokens;
	while (input[i])
	{
		if (input[i] == '\'')
			handle_single_quotes(minishell, &tokens, input, &i);
		else if (input[i] == '"')
			handle_double_quotes(minishell, &tokens, input, &i);
		else if (input[i] == '<' || input[i] == '>')
			handle_red_and_del(minishell, &tokens, input, &i);
		else if (input[i] == '|')
			handle_pipe_or_sign(minishell, &tokens, input, &i);
		else if (input[i] == '&' && input[i + 1] == '&')
			handle_and_sign(minishell, &tokens, input, &i);
		else if (input[i] == ' ' || input[i] == '\t')
			handle_spaces(minishell, &tokens, input, &i);
		else
			handle_commands(minishell, &tokens, input, &i);
		i++;
	}
	tmp = tokens;
	while (tmp)
	{
		printf("|token : %s -> type : %d|\n", tmp->token, tmp->type);
		tmp = tmp->next;
	}
}
