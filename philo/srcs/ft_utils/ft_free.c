/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:04:06 by mnaimi            #+#    #+#             */
/*   Updated: 2022/04/10 18:05:59 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo_head.h"

/* -------------------------------------------------------------------------- */

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

/* -------------------------------------------------------------------------- */
