/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:17:30 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/03/05 08:50:19 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef enum e_ordertype
{
	EAT,
	SLEEP,
	THINK,
	DIE,	
}					t_ordertype;

typedef struct s_order
{
	t_ordertype		ordertype;
	long			order_time;
	struct s_order	*next;
	struct s_order	*prev;
}					t_order;

typedef struct s_stack
{
	int				size;
	struct s_order	*head;
	struct s_order	*current;
	struct s_order	*last;
}					t_stack;

typedef struct s_schedule
{
	int	start;
	int	think;
	int	eat;
	int	sleep;
}					t_schedule;

typedef struct s_philosopher
{
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	pthread_t		thread;
	t_order			*head;
	t_stack			*stack;
	t_schedule		*schedule;
	struct s_data	*philo_info;
}				t_philosopher;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				option;
	t_philosopher	*philosophers;
	t_schedule		*schedule_list;
	pthread_mutex_t	*forks_mutexes;
	pthread_mutex_t	print_mutex;
	struct timeval	start_time;
}				t_data;

long	ft_strtol(const char *str, char **endptr, int base);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	set_data(t_data *data, int argc, char **argv);
int		set_schedule_list(t_data *data);
void	input_schedule(t_data *data, int list_len);
int		input_argv(t_data *data, int argc, char **argv);
int		ret_error(char *str);
int		argvcheck(char *str);
int		strtol_errorcheck(char *str, long check_num);
t_order	*ordernew(t_ordertype content, long time);
t_order	*ft_lstlast(t_order *lst);
void	orderadd_back(t_stack *stack, t_order *new);
// void	orderadd_back(t_order **head, t_order *new);
// void	enum_to_order(t_philosopher philo, t_order *order);
void	print_order(t_philosopher data);
// void	print_order(t_data data, int *n);

#endif // PHILOSOPHERS_H