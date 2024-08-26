/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:00:29 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/08/25 19:38:18 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_sibling_fd(t_exec *tree)
{
	if (!tree)
		return ;
	if (tree->fdin != 0)
		close(tree->fdin);
	if (tree->fdout != 1)
		close(tree->fdout);
	close_sibling_fd(tree->left);
	close_sibling_fd(tree->right);
}
