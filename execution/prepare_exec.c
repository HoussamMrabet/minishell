/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:46:43 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/07/18 09:49:44 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_pipes(t_exec *tree, int sdin, int sdout, t_minishell *mini)
{
    int fds[2];

    if (!tree)
        return ;
    if ( tree->fdin == 0)
        tree->fdin = sdin;
    if (tree->fdout == 1)
        tree->fdout = sdout;
    if (tree->type == PIPE)
    {
        pipe(fds);
        add_pipes(tree->left, sdin, fds[1], mini);
        add_pipes(tree->right, fds[0], sdout, mini);
    }
    else 
    {
        add_pipes(tree->left, sdin, sdout, mini);
        add_pipes(tree->right, sdin, sdout, mini);
    }
}
