/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:34:06 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/29 10:50:02 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_wild_files(t_minishell *m, char *token)
{
	char			*res;
	DIR				*my_dir;
	struct dirent	*files;

	res = ft_strdup("", m, &m->local);
	my_dir = opendir(ft_getcwd(m));
	if (my_dir == NULL)
		return (exit_status(1, TRUE), token);
	while (TRUE)
	{
		files = readdir(my_dir);
		if (!files)
			break ;
		if (file_match(m, token, files->d_name))
		{
			if (files->d_name[0] == '.' && token[0] != '.')
				continue ;
			res = ft_strjoin(res, "\002", m, &m->local);
			res = ft_strjoin(res, files->d_name, m, &m->local);
		}
	}
	closedir(my_dir);
	if (!res[0])
		return (ft_strdup(token, m, &m->local));
	return (res);
}

static char	*get_wildcards(t_minishell *m, char *token)
{
	size_t	i;
	char	*wildcard;

	i = 0;
	wildcard = token;
	if (!ft_strchr(wildcard, '/'))
		return (ft_strtrim(m, get_wild_files(m, token), "	 \002"));
	return (token);
}

static void	split_files(t_minishell *m, t_tokenizer **tokens)
{
	t_tokenizer	*o;
	t_tokenizer	*token;
	t_tokenizer	*new;
	char		**files;
	int			i;

	files = ft_split_local((*tokens)->token, '\002', m);
	(1) && (token = (*tokens)->next, o = *tokens, i = 0);
	while (files[i])
	{
		if (i == 0)
			(*tokens)->token = ft_strdup(files[i], m, &m->local);
		else
		{
			new = ft_malloc(m, &m->local, sizeof(t_tokenizer));
			(1) && (new->amb = o->amb, new->type = SPACES, new->lvl = o->lvl);
			new->token = ft_strdup(" ", m, &m->local);
			(1) && (new->next = token, (*tokens)->next = new, *tokens = new);
			new = ft_malloc(m, &m->local, sizeof(t_tokenizer));
			(1) && (new->amb = o->amb, new->type = o->type, new->lvl = o->lvl);
			new->token = ft_strdup(files[i], m, &m->local);
			(1) && (new->next = token, (*tokens)->next = new, *tokens = new);
		}
		i++;
	}
}

void	ft_wildcards(t_minishell *minishell, t_tokenizer **token)
{
	t_tokenizer	*tokens;

	tokens = *token;
	while (tokens)
	{
		if (tokens->type == WILD_CARD)
		{
			tokens->token = get_wildcards(minishell, tokens->token);
			if (ft_strchr(tokens->token, '\002'))
				tokens->amb = TRUE;
			split_files(minishell, &tokens);
		}
		tokens = tokens->next;
	}
}

void	merge_wildcards(t_minishell *minishell, t_tokenizer **tokens)
{
	t_tokenizer	*token;

	token = *tokens;
	while (token)
	{
		if (token->type == CMD && token->next
			&& token->next->type == WILD_CARD)
		{
			token->token = ft_strjoin(token->token,
					token->next->token, minishell, &minishell->local);
			token->next = token->next->next;
		}
		token = token->next;
	}
}
