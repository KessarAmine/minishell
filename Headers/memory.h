/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:13:56 by kmohamed          #+#    #+#             */
/*   Updated: 2023/05/09 17:51:14 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_memory_block
{
	void					*adresse;
	size_t					size;
	struct s_memory_block	*next;
}				t_memory_block;

void	*add_mem_block(void **p_head, size_t size);
void	remove_mem_block(void **p_head, void *ptr);
void	*my_malloc(void **p_head, size_t size);
void	my_free(void **p_head, void *adresse);
void	free_all_mem(void **p_head);
void	display_memory(void *p_head);
