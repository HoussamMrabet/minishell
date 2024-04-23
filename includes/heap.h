/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:55:46 by hmrabet           #+#    #+#             */
/*   Updated: 2024/04/20 08:56:28 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_block_memory
{
	void					*leak;
	struct s_block_memory	*next;
}	t_block_memory;

void	*ft_malloc(t_block_memory **memory, size_t size);
void	ft_free(t_block_memory **memory);

#endif
