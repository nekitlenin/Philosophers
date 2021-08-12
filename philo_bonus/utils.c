/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:10:16 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:29:07 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	current_time;
	long			n;

	gettimeofday(&current_time, NULL);
	n = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (n);
}

int	my_sleep(int sleep)
{
	long int	time;

	time = get_time();
	while (get_time() - time < sleep)
		usleep(50);
	return (1);
}
