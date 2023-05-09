/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:20:04 by kmohamed          #+#    #+#             */
/*   Updated: 2023/05/09 17:55:48 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Headers/memory.h"

void	*add_mem_block(void **p_head, size_t size)
{
	t_memory_block *block;

	block = (t_memory_block*) malloc(sizeof(t_memory_block) + size);
	if (!block)
		return 0;
	block->adresse = malloc(size);
	if (!block->adresse)
		return 0;
	block->size = size;
	block->next = *p_head;
	*p_head = block;
	return (block->adresse);
}

void	remove_mem_block(void **p_head, void *ptr)
{
	t_memory_block *block;
	t_memory_block *prev;

	block = *p_head;
	prev = NULL;
	while (block)
	{
		if (block->adresse == ptr)
		{
			printf("found adress == %p\n", block->adresse);
			if (prev == NULL)
				*p_head = block->next;
			else
				prev->next = block->next;
			// free(block->adresse);
			// block->adresse = ((void *)0);
			free(block);
			block = ((void *)0);
			break;
		}
		prev = block;
		block = block->next;
	}
	// display_memory(*p_head);
}

void	*my_malloc(void **p_head, size_t size)
{
	return (add_mem_block(p_head, size));
}

void	my_free(void **p_head, void *adresse)
{
	remove_mem_block(p_head, adresse);
	free(adresse);
}

void	free_all_mem(void **p_head)
{
	t_memory_block	*node;
	t_memory_block	*next;
	int i = 1;

	if (p_head == NULL)
		return ;
	next = NULL;
	node = *p_head;
	while (node != NULL && node->adresse)
	{
		// printf("removing node %p : adresse = %p | next = %p\n", node, node->adresse, node->next);
		next = node->next;
		free(node->adresse);
		node->adresse = ((void *) 0);
		// printf("node adresse = %p \n", node->adresse);
		free(node);
		node = ((void *) 0);
		node = next;
		i++;
	}
	*p_head = NULL;
}

void display_memory(void *p_head)
{
	t_memory_block	*temp;
	int i = 1;
	printf("\t=====[Heap Allocations]====\n");
	temp = p_head;
	while (temp != NULL)
	{
		printf("block_%d/%p adresse = %p\n", i, temp, temp->adresse);
		temp = temp->next;
		i++;
	}
	printf("\t===========================\n");
}