/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofiles_checker_builtins.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:09:07 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/08/26 17:44:08 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ambig_builtin(t_bool val, char *str)
{
	if (val)
	{
		ft_putstr_fd("minishell: ", 2);
		reverse_str(&str);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		exit_status(1, 1);
		return (1);
	}
	return (0);
}

int	open_append_builtin(t_exec *tree, int *fdout)
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

int	open_rdout_builtin(t_exec *tree, int *fdout)
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

int	open_rdin_bultin(t_exec *tree, int *fdin)
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

int	open_files_builtin(t_exec *tree)
{
	int	fds[2];

	(1) && (fds[0] = tree->fdin, fds[1] = tree->fdout);
	while (tree->iofiles)
	{
		if (tree->iofiles->type == APPEND && open_append_builtin(tree, &fds[1]))
			return (1);
		else if (tree->iofiles->type == OUT_RED && open_rdout_builtin(tree, &fds[1]))
			return (1);
		else if (tree->iofiles->type == IN_RED && open_rdin_bultin(tree, &fds[0]))
			return (1);
		else if (tree->iofiles->type == DEL)
		{
			if (close_fds_child_btn(fds[0], tree->fdout, tree))
				return (1);
			fds[0] = tree->fdin;
		}
		tree->iofiles = tree->iofiles->next;
	}
	if (tree->fdout != fds[1] && tree->fdout != 1)
		return (catch_error_builtin(close(tree->fdout), NULL), 1);
	if (tree->fdin != fds[0] && tree->fdin != 0)
		return (catch_error_builtin(close(tree->fdin), NULL), 1);
	if (!tree->tokens)
		return (1);
	return (tree->fdin = fds[0], tree->fdout = fds[1], 0);
}
