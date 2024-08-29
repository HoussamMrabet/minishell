/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:11:00 by hmrabet           #+#    #+#             */
/*   Updated: 2024/08/29 10:56:20 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	getback_spaces(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\002')
			(*str)[i] = 32;
		i++;
	}
}

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
	if (fd == -1)
		ft_exit("minishell: open failed", 1, m);
	m->max_fd = fd;
	if (token->type == DELIM)
	{
		handle_text_expand(m, NULL, &file_c);
		getback_spaces(&file_c);
	}
	write(fd, file_c, ft_strlen(file_c));
	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
		ft_exit("minishell: open failed", 1, m);
	m->max_fd = fd;
	unlink(file);
	(1) && (token->token = ft_itoa(m, &m->local, fd), file_c = NULL);
}

static void	here_doc1(t_minishell *m, t_tokenizer **token)
{
	char		*delim;
	char		*file_c;

	delim = NULL;
	file_c = NULL;
	if ((*token)->type == DEL)
	{
		(1) && (file_c = ft_strdup("", m, &m->local), *token = (*token)->next);
		((*token)->type == SPACES) && (*token = (*token)->next);
		while (1)
		{
			(delim) && (file_c = ft_strjoin(file_c, delim, m, &m->local));
			(delim) && (file_c = ft_strjoin(file_c, "\n", m, &m->local));
			delim = ft_readline(m, "> ", FALSE);
			if (!delim || !ft_strcmp(delim, (*token)->token))
				break ;
		}
		here_doc2(m, *token, file_c);
	}
}

int	here_doc(t_minishell *m)
{
	t_tokenizer	*token;
	int			secureinput;
	int			status;

	status = 0;
	secureinput = dup(0);
	signal(SIGINT, heredoc_signal);
	token = m->tokens;
	while (token)
	{
		here_doc1(m, &token);
		if (heredoc_status(0, FALSE))
		{
			status = 1;
			break ;
		}
		token = token->next;
	}
	heredoc_status(0, TRUE);
	dup2(secureinput, 0);
	close(secureinput);
	signal(SIGINT, handle_sigint);
	tcgetattr(STDIN_FILENO, &m->termios);
	return (status);
}
