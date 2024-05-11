/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:34:06 by hmrabet           #+#    #+#             */
/*   Updated: 2024/05/11 18:02:33 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	file_match(char *token, const char *file)//
{
	int	i;
	int	j;

	(1) && (i = 0, j = 0);
	while (token[i] || file[i + j])
	{
		if (token[i] != '*' && (token[i] != file[i + j]))
			return (FALSE);
		else if (token[i] == '*')
		{
			if (token[i] == '*' && !file[i + j])
				return (TRUE);
			i++;
			while (file[i + j])
			{
				if (file[i + j] == token[i])
					break ;
				j++;
			}
			if (!file[i + j] && token[i])
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static char	*get_wild_files(t_minishell *minishell, char *token)
{
	char			*res;
	DIR				*my_dir;
	struct dirent	*files;

	res = ft_strdup("", &minishell->local);
	my_dir = opendir(get_env_value(minishell, "PWD"));
	if (my_dir == NULL)
	{
		perror("Unable to open directory");
		return (NULL);
	}
	while (TRUE)
	{
		files = readdir(my_dir);
		if (!files)
			break ;
		if (file_match(token, files->d_name))
		{
			res = ft_strjoin(res, " ", &minishell->local);
			res = ft_strjoin(res, files->d_name, &minishell->local);
		}
	}
	closedir(my_dir);
	return (res);
}

static char	*get_wildcards(t_minishell *minishell, char *token)
{
	size_t	i;
	char	*wildcard;

	i = 0;
	wildcard = token;
	if (!ft_strchr(wildcard, '/'))
		return (get_wild_files(minishell, token));
	return (token);
}

void	ft_wildcards(t_minishell *minishell)
{
	t_tokenizer	*tokens;

	tokens = minishell->tokens;
	while (tokens)
	{
		if (tokens->type == WILD_CARD)
			tokens->token = get_wildcards(minishell, tokens->token);
		tokens = tokens->next;
	}
}

void	merge_wildcards(t_minishell *minishell)
{
	t_tokenizer	*token;

	token = minishell->tokens;
	while (token)
	{
		if (token->type == CMD && token->next
			&& token->next->type == WILD_CARD)
		{
			token->token = ft_strjoin(token->token,
					token->next->token, &minishell->local);
			token->next = token->next->next;
		}
		token = token->next;
	}
}
