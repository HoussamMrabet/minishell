/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofiles_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:48:56 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/08/26 05:41:34 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_ambig(t_minishell *mini, t_bool val, char *str)
{
	if (val)
	{
		ft_putstr_fd("minishell: ", 2);
		reverse_str(&str);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		ft_exit(NULL, 1, mini);
	}
}

void	open_append(t_minishell *mini, t_exec *tree, int *fdout)
{
	check_ambig(mini, tree->iofiles->amb, tree->iofiles->token);
	close_fds_child(mini, tree->fdin, *fdout, tree);
	*fdout = open(tree->iofiles->token, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (*fdout == -1)
		catch_error(mini, 1, tree->iofiles->token);
}

void	open_rdout(t_minishell *mini, t_exec *tree, int *fdout)
{
	check_ambig(mini, tree->iofiles->amb, tree->iofiles->token);
	close_fds_child(mini, tree->fdin, *fdout, tree);
	*fdout = open(tree->iofiles->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fdout == -1)
		catch_error(mini, 1, tree->iofiles->token);
}

void	open_rdin(t_minishell *mini, t_exec *tree, int *fdin)
{
	check_ambig(mini, tree->iofiles->amb, tree->iofiles->token);
	close_fds_child(mini, *fdin, tree->fdout, tree);
	*fdin = open(tree->iofiles->token, O_RDWR);
	if (*fdin == -1)
		catch_error(mini, 1, tree->iofiles->token);
}

void	open_files(t_minishell *mini, t_exec *tree)
{
	int	fds[2];

	(1) && (fds[0] = tree->fdin, fds[1] = tree->fdout);
	while (tree->iofiles)
	{
		if (tree->iofiles->type == APPEND)
			open_append(mini, tree, &fds[1]);
		else if (tree->iofiles->type == OUT_RED)
			open_rdout(mini, tree, &fds[1]);
		else if (tree->iofiles->type == IN_RED)
			open_rdin(mini, tree, &fds[0]);
		else if (tree->iofiles->type == DEL)
		{
			close_fds_child(mini, fds[0], tree->fdout, tree);
			fds[0] = tree->fdin;
		}
		tree->iofiles = tree->iofiles->next;
	}
	if (tree->fdout != fds[1] && tree->fdout != 1)
		catch_error(mini, close(tree->fdout), NULL);
	if (tree->fdin != fds[0] && tree->fdin != 0)
		catch_error(mini, close(tree->fdin), NULL);
	if (!tree->tokens)
		ft_exit(NULL, 0, mini);
	1 && (tree->fdin = fds[0], tree->fdout = fds[1]);
}
