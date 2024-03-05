/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_order.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 07:35:30 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/03/04 21:38:01 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	enum_to_order(t_philosopher philo, t_order *order)
// {
// 	if (order->ordertype == 0)
// 		printf("%ld ms Philosopher %d is eating.\n", \
// 			order->order_time, philo.id);
// 	else if (order->ordertype == 1)
// 		printf("%ld ms Philosopher %d is sleeping.\n", \
// 			order->order_time, philo.id);
// 	else if (order->ordertype == 2)
// 		printf("%ld ms Philosopher %d is thinking.\n", \
// 			order->order_time, philo.id);
// 	else if (order->ordertype == 3)
// 		printf("%ld ms Philosopher %d is die.\n", \
// 			order->order_time, philo.id);
// }

// void	print_order(t_philosopher data)
// {
// 	if (data.head == NULL)
// 		return ;
// 	while (data.head->next != NULL)
// 	{
// 		enum_to_order (data, data.head);
// 		data.head = data.head->next;
// 	}
// 	enum_to_order (data, data.head);
// 	// data->head = data->head->next;
// }

// void	print_order(t_data *data, int *n)
// {
// 	int	i;

// 	i = 0;
// 	if (data.head == NULL)
// 		return ;
// 	while (n > i && data.head->next != NULL)
// 	{
// 		// enum_to_order (data, data.head);
// 		data.head = data.head->next;
// 		i++;
// 	}
// 	while (data->num_philo > i)
// 	{
// 		i += count_order(data->philosophers[i], n);
// 		if (i == data->num_philo)
// 		{
// 			print_order(data, &count);
// 			break ;
// 		}
// 	}
// 	enum_to_order (data, data.head);
// 	// data->head = data->head->next;
// }
