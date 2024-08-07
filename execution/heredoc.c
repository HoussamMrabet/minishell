/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:11:00 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/16 13:59:26 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_name(t_minishell *mini)
{
	char	*test;
	int		num;

	num = 0;
	while (num <= OPEN_MAX)
	{
		test = ft_strjoin("/tmp/", ft_itoa(mini, &mini->local, num),
				mini, &mini->local);
		if (access(test, F_OK) != 0)
			return (test);
		num++;
	}
	return (NULL);
}

static void	here_doc2(t_minishell *m, t_tokenizer *token, char *file_c)
{
	char	*file;
	int		fd;

	(1) && (file = get_heredoc_name(m));
	fd = open(file, O_RDWR | O_CREAT, 0644);
	m->max_fd = fd;
	if (token->type == DELIM)
		handle_text_expand(m, NULL, &file_c);
	write(fd, file_c, ft_strlen(file_c));
	fd = open(file, O_RDONLY, 0644);
	m->max_fd = fd;
	unlink(file);
	(1) && (token->token = ft_itoa(m, &m->local, fd), file_c = NULL);
}

void	here_doc(t_minishell *m)
{
	t_tokenizer	*token;
	char		*delim;
	char		*file_c;

	(1) && (token = m->tokens, delim = NULL, file_c = NULL);
	while (token)
	{
		if (token->type == DEL)
		{
			(1) && (file_c = ft_strdup("", m, &m->local), token = token->next);
			(token->type == SPACES) && (token = token->next);
			while (1)
			{
				(delim) && (file_c = ft_strjoin(file_c, delim, m, &m->local));
				(delim) && (file_c = ft_strjoin(file_c, "\n", m, &m->local));
				delim = ft_readline(m, "> ", FALSE);
				if (!delim || !ft_strcmp(delim, token->token))
					break ;
			}
			here_doc2(m, token, file_c);
		}
		token = token->next;
	}
}
