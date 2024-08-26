/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:46:43 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/08/25 16:12:26 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pipes(t_exec *tree, int sdin, int sdout, t_minishell *mini)
{
	int	fds[2];

	if (!tree)
		return ;
	if (tree->fdin == 0)
		tree->fdin = sdin;
	if (tree->fdout == 1)
		tree->fdout = sdout;
	if (tree->type == PIPE)
	{
		if (pipe(fds) == -1)
			ft_exit("minishell: Pipe failed", 1, mini);
		add_pipes(tree->left, sdin, fds[1], mini);
		add_pipes(tree->right, fds[0], sdout, mini);
	}
	else
	{
		add_pipes(tree->left, sdin, sdout, mini);
		add_pipes(tree->right, sdin, sdout, mini);
	}
}
