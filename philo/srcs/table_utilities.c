/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:37:39 by mnaimi            #+#    #+#             */
/*   Updated: 2022/04/18 02:38:11 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_head.h"

/* -------------------------------------------------------------------------- */

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_safely(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->philos[(philo->id + 1) % \
		philo->table->philo_count].fork);
	print_safely(philo, "has taken a fork");
}

/* -------------------------------------------------------------------------- */

static void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->philos[(philo->id + 1) % \
		philo->table->philo_count].fork);
	pthread_mutex_unlock(&philo->fork);
}

/* -------------------------------------------------------------------------- */

static void	*routine(void *ptr)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)ptr;
	table = philo->table;
	if (philo->id % 2)
		usleep(500);
	while (table->status == ON)
	{
		take_forks(philo);
		print_safely(philo, "is eating");
		philo->last_meal_time = ft_get_usec_timestamp();
		ft_usleep(table->time_to_eat);
		put_forks(philo);
		philo->eat_count++;
		print_safely(philo, "is sleeping");
		ft_usleep(table->time_to_slp);
		print_safely(philo, "is thinking");
		if (philo->eat_count == table->count_to_eat)
			table->have_eaten += 1;
	}
	return (NULL);
}

/* -------------------------------------------------------------------------- */

static int	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].table = table;
		table->philos[i].id = i;
		table->philos[i].eat_count = 0;
		table->philos[i].stat = 0;
		if (pthread_mutex_init(&table->philos[i].fork, NULL) != 0)
			return (ft_perror(2, "Mutex Init Failure"), -1);
	}
	i = -1;
	while (++i < table->philo_count)
	{
		if (pthread_create(&table->philos[i].ph_thrd, NULL, &routine, \
			(void *)&table->philos[i]) != 0)
			return (ft_perror(2, "Thread Creation Error"), -1);
		table->philos[i].last_meal_time = ft_get_usec_timestamp();
		if (pthread_detach(table->philos[i].ph_thrd) != 0)
			return (ft_perror(2, "Thread Detaching Error"), -1);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */

int	init_table(t_table *table)
{
	table->status = ON;
	table->allow_print = ON;
	table->have_eaten = 0;
	table->end_philos = 0;
	table->philos = (t_philo *)ft_calloc(table->philo_count, sizeof(t_philo));
	if (table->philos == NULL)
		return (ft_perror(2, "Malloc Failure"), -1);
	if (pthread_mutex_init(&table->msg_mtx, NULL) != 0)
		return (ft_perror(2, "Mutex Init Failure"), -1);
	if (init_philos(table) != 0)
		return (-1);
	return (0);
}

/* -------------------------------------------------------------------------- */
