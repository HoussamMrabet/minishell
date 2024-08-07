/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:02:48 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/09 06:01:09 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_del(t_minishell *minishell, char *input)
{
	char	*del;
	int		j;
	int		i;

	(1) && (j = 0, i = 0);
	while (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>'
		&& input[i] != '|' && input[i] != '&' && input[i] != '('
		&& input[i] != ')')
		(1) && (((input[i] != '\'' && input[i] != '"') && (j++)), i++);
	(1) && (i = 0, del = ft_malloc(minishell, &minishell->local, j + 1));
	j = 0;
	while (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>'
		&& input[i] != '|' && input[i] != '&' && input[i] != '('
		&& input[i] != ')')
	{
		if (input[i] != '\'' && input[i] != '"')
			(1) && (del[j] = input[i], j++);
		i++;
	}
	del[j] = '\0';
	return (del);
}

static void	get_here_doc_input(t_minishell *minishell, char *delim)
{
	char	*del;

	del = NULL;
	while (1)
	{
		del = ft_readline(minishell, "> ", FALSE);
		if (!del || !ft_strcmp(delim, del))
			break ;
	}
}

void	here_doc_err(t_minishell *minishell, char *input)
{
	char	*delim;
	char	*del;
	int		i;
	t_bool	q[2];

	(1) && (i = 0, del = NULL, q[0] = FALSE, q[1] = FALSE);
	while (input[i] && i < minishell->err.pos)
	{
		if (input[i] == '\'' && !q[1])
			q[0] = !q[0];
		if (input[i] == '"' && !q[0])
			q[1] = !q[1];
		if (!q[0] && !q[1] && input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i] == ' ')
				i++;
			delim = get_del(minishell, input + i);
			if (delim && delim[0])
				get_here_doc_input(minishell, delim);
		}
		i++;
	}
}
