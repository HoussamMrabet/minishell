/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:55:49 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/20 09:58:31 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

void	*ft_malloc(t_block_memory **memory, size_t size)
{
	void			*res;
	t_block_memory	*new;
	t_block_memory	*tmp;

	tmp = *memory;
	res = malloc(size);
	if (!res)
		return (NULL);
	new = (t_block_memory *)malloc(sizeof(t_block_memory));
	if (!new)
	{
		free(res);
		return (NULL);
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
		write(1, "pass\n", 5);
		to_hold = to_free->next;
		free(to_free->leak);
		write(1, "pass\n", 5);
		free(to_free);
		to_free = to_hold;
	}
}
