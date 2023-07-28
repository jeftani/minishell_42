/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 08:27:07 by ajeftani          #+#    #+#             */
/*   Updated: 2023/07/27 23:26:29 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void addToLinkedList(t_Node** head, void* address) {
    t_Node* newNode = (t_Node*)malloc(sizeof(t_Node));
    newNode->address = address;
    newNode->next = *head;
    *head = newNode;
}

void* ft_malloc(size_t size) {
    static t_Node* head = NULL;

    void* ptr = malloc(size);
    if (ptr != NULL) {
        if (head == NULL) {
            head = (t_Node*)malloc(sizeof(t_Node));
            head->address = NULL;
            head->next = NULL;
        }
        addToLinkedList(&head, ptr);
    }
    return ptr;
}





