/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:04:02 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/03/05 08:50:31 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_order	*ordernew(t_ordertype content, long time)
{
	t_order	*node;

	node = ft_calloc(sizeof(t_order), 1);
	if (!node)
		return (NULL);
	node->ordertype = (t_ordertype)content;
	node->order_time = time;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_order	*ft_lstlast(t_order *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	orderadd_back(t_stack *stack, t_order *new)
{
	if (stack == NULL || new == NULL)
		return ;
	if (stack->head == NULL)
	{
		stack->head = new;
		stack->current = NULL;
		stack->last = new;
		stack->size = 1;
	}
	else
	{
		// stack->last = ft_lstlast (*head);
		stack->last->next = new;
		new->prev = stack->last;
		stack->last = new;
		stack->size += 1;
	}
}


// void	orderadd_back(t_order **head, t_order *new)
// {
// 	t_order	*temp_last;

// 	if (head == NULL || new == NULL)
// 		return ;
// 	if (*head == NULL)
// 	{
// 		*head = new;
// 	}
// 	else
// 	{
// 		temp_last = ft_lstlast (*head);
// 		temp_last->next = new;
// 		new->prev = temp_last;
// 	}
// }
