/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:37:39 by mnaimi            #+#    #+#             */
/*   Updated: 2022/05/07 16:33:33 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_head.h"

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

long	ft_get_usec_timestamp(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

/* -------------------------------------------------------------------------- */

void	ft_usleep(long time_to_sleep)
{
	long	time;

	time = ft_get_usec_timestamp();
	while (ft_get_usec_timestamp() - time < time_to_sleep)
		usleep(10);
}

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

void	ft_perror(int type, char *cause)
{
	if (type == 1)
		write(2, RED"\033[4m\nError\033[0m\t", 20);
	else if (type == 2)
		write(2, YEL"\nWarning"NNN, 17);
	write(2, cause, ft_strlen(cause));
	write(2, "\n\n", 2);
}

/* -------------------------------------------------------------------------- */
