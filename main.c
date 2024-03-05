/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:35:21 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/03/05 07:56:53 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(t_data *data)
{
	struct timeval	current;
	long			milliseconds;

	gettimeofday(&current, NULL);
	milliseconds = (current.tv_sec - data->start_time.tv_sec) * 1000;
	milliseconds += (current.tv_usec - data->start_time.tv_usec) / 1000;
	return (milliseconds);
}

// long	get_time(t_data *data)
// {
// 	struct timeval	current;
// 	long			milliseconds;

// 	gettimeofday(&current, NULL);
// 	milliseconds = current.tv_sec * 1000;
// 	milliseconds += current.tv_usec / 1000;
// 	return (milliseconds);
// }

char	*enum_to_order(t_ordertype content)
{
	if (content == 0)
		return ("eat");
	else if (content == 1)
		return ("sleep");
	else if (content == 2)
		return ("think");
	else if (content == 3)
		return ("die");
	return (NULL);
}

int	printp(t_ordertype content, long time, t_philosopher *philo)
{
	// pthread_t	print_thread;
	char		*order;

	order = enum_to_order(content);
	// pthread_mutex_lock(&philo->philo_info->print_mutex);
	printf("%ld ms Philosopher %d is %sing.\n", time, philo->id, order);
	// pthread_mutex_unlock(&philo->philo_info->print_mutex);
	return (0);
}

int	first_think(t_philosopher *philo, long time)
{
	long	current_time;

	// printf("%ld ms Philosopher %d is thinking.\n", time, philo->id);
	current_time = get_time(philo->philo_info);
	printp(THINK, time, philo);
	while (philo->schedule->start > current_time - time)
	{
		usleep(50);
		current_time = get_time(philo->philo_info);
	}
	return (current_time);
}

int	func_think(t_philosopher *philo, long time)
{
	long	current_time;

	// printf("%ld ms Philosopher %d is thinking.\n", time, philo->id);
	current_time = get_time(philo->philo_info);
	printp(THINK, time, philo);
	while (philo->schedule->think > current_time - time)
	{
		usleep(50);
		current_time = get_time(philo->philo_info);
	}
	return (current_time);
}

int	func_eat(t_philosopher *philo, long time)
{
	long	current_time;

	// printf("%ld ms Philosopher %d is eating.\n", time, philo->id);
	current_time = get_time(philo->philo_info);
	printp(EAT, time, philo);
	while (philo->schedule->eat > current_time - time)
	{
		usleep(50);
		current_time = get_time(philo->philo_info);
	}
	return (current_time);
}

int	func_sleep(t_philosopher *philo, long time)
{
	long	current_time;

	// printf("%ld ms Philosopher %d is sleeping.\n", time, philo->id);
	current_time = get_time(philo->philo_info);
	printp(SLEEP, time, philo);
	while (philo->schedule->sleep > current_time - time)
	{
		usleep(50);
		current_time = get_time(philo->philo_info);
	}
	return (current_time);
}

void	chain_of_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_detach(data->philosophers[i].thread);
		i++;
	}
}

// void	*print(void *arg)
// {
// 	t_philosopher	*philo;
// 	int		i;
// 	int		flag;
// 	int		count;

// 	philo = (t_philosopher *)arg;
// 	i = 0;
// 	count = 0;
// 	while (1)
// 	{
// 		i = 0;
// 		while (data->num_philo > i)
// 		{
// 			i += count_order(data->philosophers[i], count);
// 			if (i == data->num_philo)
// 			{
// 				print_order(philo, &count);
// 				break ;
// 			}
// 		}
// 	}
// }

void	*action(void *arg)
{
	t_philosopher	*philo;
	pthread_mutex_t	mutex;
	// pthread_t		print_thread;
	long			time;
	// long			start_time;
	int				i;

	// pthread_create(print_thread, NULL, print, arg);
	i = 0;
	philo = (t_philosopher *)arg;
	time = get_time(philo->philo_info);
	pthread_mutex_lock(&philo->philo_info->print_mutex);
	first_think(philo, time);
	pthread_mutex_unlock(&philo->philo_info->print_mutex);
	while (1)
	{
		// time = get_time(philo->philo_info);
		pthread_mutex_lock(&philo->philo_info->forks_mutexes[philo->left_fork_id]);
		pthread_mutex_lock(&philo->philo_info->forks_mutexes[philo->right_fork_id]);
		time = func_eat(philo, time);
		pthread_mutex_unlock(&philo->philo_info->forks_mutexes[philo->left_fork_id]);
		pthread_mutex_unlock(&philo->philo_info->forks_mutexes[philo->right_fork_id]);
		pthread_mutex_lock(&mutex);
		time = func_sleep(philo, time);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex);
		time = func_think(philo, time);
		pthread_mutex_unlock(&mutex);
		// pthread_mutex_lock(&philo->philo_info->print_mutex);
		// time = get_time(philo->philo_info) - start_time;
		// printf("start\n");
		// print_order(*philo);
		// pthread_mutex_unlock(&philo->philo_info->print_mutex);
		i++;
		if (i == 10)
			break ;
	}
	return (NULL);
}

// int	cunt()
// {
	
// }


void	create_pthread(t_data *data)
{
	int			i;
	// pthread_t	print_thread;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, action, \
			&data->philosophers[i]))
			ret_error("create");
		i++;
	}
	// pthread_create(print_thread, NULL, print, data);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ret_error("Invalid arguments"));
	memset(&data, 0, sizeof(data));
	set_data(&data, argc, argv);
	create_pthread(&data);
}


// int	first_think(t_philosopher *philo)
// {
// 	orderadd_back(&(*philo).head, ordernew(THINK, get_time(philo->philo_info)));
// 	usleep(philo->schedule->start * 1000);
// 	return (0);
// }

// int	func_think(t_philosopher *philo)
// {
// 	orderadd_back(&(*philo).head, ordernew(THINK, get_time(philo->philo_info)));
// 	usleep(philo->schedule->think * 1000);
// 	return (0);
// }

// int	func_eat(t_philosopher *philo, long time)
// {
// 	long	current_time;

// 	printf("%ld ms Philosopher %d is thinking.\n", time, philo->id);
// 	current_time = get_time(philo->philo_info);
// 	// orderadd_back(&(*philo).head, ordernew(EAT, time));
// 	while (philo->schedule->eat >= current_time - time)
// 	{
// 		// usleep(philo->schedule->eat * 1000);
// 		usleep(50);
// 		current_time = get_time(philo->philo_info);
// 	}
// 	return (current_time);
// }

// int	func_sleep(t_philosopher *philo)
// {
// 	orderadd_back(&(*philo).head, ordernew(SLEEP, get_time(philo->philo_info)));
// 	usleep(philo->schedule->sleep * 1000);
// 	return (0);
// }
