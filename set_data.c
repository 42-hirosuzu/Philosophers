/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:47:05 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/02/27 02:39:56 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	input_argv(t_data *data, int argc, char **argv)
{
	int	i;

	i = 1;
	while (argc > i)
	{
		if (argvcheck(argv[i]) || \
			strtol_errorcheck(argv[i], ft_strtol(argv[i], NULL, 0)))
			return (ret_error("Invalid arguments"));
		i++;
	}
	data->num_philo = ft_strtol(argv[1], NULL, 0);
	data->time_to_die = ft_strtol(argv[2], NULL, 0);
	data->time_to_eat = ft_strtol(argv[3], NULL, 0);
	data->time_to_sleep = ft_strtol(argv[4], NULL, 0);
	if (argc == 6)
		data->option = ft_strtol(argv[5], NULL, 0);
	return (0);
}

void	input_schedule(t_data *data, int list_len)
{
	int	i;

	i = 0;
	data->schedule_list = ft_calloc(list_len, sizeof(t_schedule));
	while (list_len > i)
	{
		data->schedule_list[i].eat = data->time_to_eat;
		data->schedule_list[i].sleep = data->time_to_sleep;
		data->schedule_list[i].think = \
			abs(data->time_to_eat - data->time_to_sleep);
		i++;
	}
}

int	set_schedule_list(t_data *data)
{
	int	list_len;

	if (data->num_philo % 2 == 0)
		list_len = 2;
	else
		list_len = 3;
	input_schedule(data, list_len);
	if (list_len == 2)
	{
		data->schedule_list[0].start = 0;
		data->schedule_list[1].start = data->schedule_list->think;
	}
	else
	{
		data->schedule_list[0].start = 0;
		data->schedule_list[1].start = data->schedule_list->eat;
		data->schedule_list[2].start = data->schedule_list->eat * 2;
	}
	return (list_len);
}

void	set_data(t_data *data, int argc, char **argv)
{
	int	i;
	int	list_len;

	i = 0;
	input_argv(data, argc, argv);
	data->philosophers = ft_calloc(data->num_philo, sizeof(t_philosopher));
	data->forks_mutexes = ft_calloc(data->num_philo, sizeof(pthread_mutex_t));
	list_len = set_schedule_list(data);
	while (i < data->num_philo)
	{
		memset(&data->philosophers[i], 0, sizeof(t_philosopher));
		data->philosophers[i].id = i;
		data->philosophers[i].left_fork_id = i;
		data->philosophers[i].right_fork_id = (i + 1) % data->num_philo;
		data->philosophers[i].philo_info = data;
		pthread_mutex_init(&data->forks_mutexes[i], NULL);
		data->philosophers[i].schedule = &data->schedule_list[i % list_len];
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	gettimeofday(&data->start_time, NULL);
}
