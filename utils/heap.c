/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:55:49 by hmrabet           #+#    #+#             */
/*   Updated: 2024/07/16 13:35:10 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(t_minishell *minishell, t_block_memory **memory, size_t size)
{
	void			*res;
	t_block_memory	*new;
	t_block_memory	*tmp;

	tmp = *memory;
	res = malloc(size);
	if (!res)
		ft_exit("Allocation error!", 1, minishell);
	new = (t_block_memory *)malloc(sizeof(t_block_memory));
	if (!new)
	{
		free(res);
		ft_exit("Allocation error!", 1, minishell);
	}
	new->leak = res;
	new->next = NULL;
	if (!tmp)
		*memory = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (res);
}

void	ft_free(t_block_memory **memory)
{
	t_block_memory	*to_free;
	t_block_memory	*to_hold;

	to_free = *memory;
	while (to_free)
	{
		to_hold = to_free->next;
		free(to_free->leak);
		free(to_free);
		to_free = to_hold;
	}
	*memory = NULL;
}

void	ft_free_all(t_minishell *minishell)
{
	ft_free(&minishell->local);
	ft_free(&minishell->global);
}
