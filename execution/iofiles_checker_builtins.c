/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofiles_checker_builtins.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:09:07 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/08/26 18:08:52 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	red_app(t_exec *tree, int *fdout)
{
	if (check_ambig_builtin(tree->iofiles->amb, tree->iofiles->token))
		return (1);
	if (close_fds_child_btn(tree->fdin, *fdout, tree))
		return (1);
	*fdout = open(tree->iofiles->token, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (*fdout == -1)
		return (catch_error_builtin(1, tree->iofiles->token), 1);
	return (0);
}

static int	red_out(t_exec *tree, int *fdout)
{
	if (check_ambig_builtin(tree->iofiles->amb, tree->iofiles->token))
		return (1);
	if (close_fds_child_btn(tree->fdin, *fdout, tree))
		return (1);
	*fdout = open(tree->iofiles->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fdout == -1)
		return (catch_error_builtin(1, tree->iofiles->token), 1);
	return (0);
}

static int	red_in(t_exec *tree, int *fdin)
{
	if (check_ambig_builtin(tree->iofiles->amb, tree->iofiles->token))
		return (1);
	if (close_fds_child_btn(*fdin, tree->fdout, tree))
		return (1);
	*fdin = open(tree->iofiles->token, O_RDWR);
	if (*fdin == -1)
		return (catch_error_builtin(1, tree->iofiles->token), 1);
	return (0);
}

static int	destroy_fds(t_exec *tree, int fd0, int fd1)
{
	if (tree->fdout != fd1 && tree->fdout != 1)
		return (catch_error_builtin(close(tree->fdout), NULL), 1);
	if (tree->fdin != fd0 && tree->fdin != 0)
		return (catch_error_builtin(close(tree->fdin), NULL), 1);
	if (!tree->tokens)
		return (1);
	return (0);
}

int	open_files_builtin(t_exec *tree)
{
	int	fds[2];

	(1) && (fds[0] = tree->fdin, fds[1] = tree->fdout);
	while (tree->iofiles)
	{
		if (tree->iofiles->type == APPEND && red_app(tree, &fds[1]))
			return (1);
		else if (tree->iofiles->type == OUT_RED && red_out(tree, &fds[1]))
			return (1);
		else if (tree->iofiles->type == IN_RED && red_in(tree, &fds[0]))
			return (1);
		else if (tree->iofiles->type == DEL)
		{
			if (close_fds_child_btn(fds[0], tree->fdout, tree))
				return (1);
			fds[0] = tree->fdin;
		}
		tree->iofiles = tree->iofiles->next;
	}
	if (destroy_fds(tree, fds[0], fds[1]))
		return (1);
	return (tree->fdin = fds[0], tree->fdout = fds[1], 0);
}
