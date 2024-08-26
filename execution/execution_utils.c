/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:40 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/08/26 05:41:55 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_length(t_tokenizer *tokens)
{
	int			i;
	t_tokenizer	*t;

	i = 0;
	t = tokens;
	while (t)
	{
		if (t->type != SPACES)
			i++;
		t = t->next;
	}
	return (i);
}

char	**to_array(t_tokenizer *tokens, t_minishell *mini)
{
	int		len;
	char	**res;
	int		i;

	if (!tokens)
		return (NULL);
	len = tokens_length(tokens);
	i = 0;
	res = (char **)ft_malloc(mini, &mini->local, sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	while (i < len && tokens)
	{
		if (tokens->type != SPACES)
		{
			res[i] = tokens->token;
			i++;
		}
		tokens = tokens->next;
	}
	res[i] = NULL;
	return (res);
}

void	catch_error(t_minishell *mini, int i, char *command)
{
	if (i != 0)
	{
		if (i == 127 || i == -1)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		else if (i == 126)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		else
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd(" : ", 2);
			ft_putstr_fd(command, 2);
			ft_putchar_fd('\n', 2);
		}
		ft_exit(NULL, i, mini);
	}
}

void	close_fds_child(t_minishell *mini, int fdin, int fdout, t_exec *tree)
{
	if (fdin == tree->fdin && fdout == tree->fdout)
		return ;
	if (fdin != tree->fdin && fdin != 0)
		catch_error(mini, close(fdin), "close");
	else if (fdout != tree->fdout && fdout != 1)
		catch_error(mini, close(fdout), "close");
}
