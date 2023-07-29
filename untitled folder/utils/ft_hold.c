/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hold.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:06:19 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/29 10:47:06 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	addtolinkedlist(t_Node **head, void *address)
{
	t_Node	*newnode;

	newnode = (t_Node *)malloc(sizeof(t_Node));
	newnode->address = address;
	newnode->next = *head;
	*head = newnode;
}

void	*ft_malloc(size_t size)
{
	static t_Node	*head = NULL;
	void			*ptr;

	ptr = malloc(size);
	if (ptr != NULL)
	{
		if (head == NULL)
		{
			head = (t_Node *)malloc(sizeof(t_Node));
			head->address = NULL;
			head->next = NULL;
		}
		addtolinkedlist(&head, ptr);
	}
	return (ptr);
}
