/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutom_atoll.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:13:46 by mnaimi            #+#    #+#             */
/*   Updated: 2022/04/10 17:46:45 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo_head.h"

/* -------------------------------------------------------------------------- */

int64_t	ft_custom_atoll(const char *str)
{
	size_t	i;
	int64_t	sum;
	char	sign;

	i = 0;
	sum = 0;
	sign = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
		sign = str[i] - '+';
	while (ft_isdigit(str[i]))
	{
		sum = (sum * 10) + (str[i++] - '0');
		if (sum > LONG_MAX || (sign && -(sum) < LONG_MIN))
			return (ft_perror(1, "ft_custom_atoll", "Number out of range"), 0);
	}
	if (sign)
		sum *= -1;
	return (sum);
}

/* -------------------------------------------------------------------------- */
