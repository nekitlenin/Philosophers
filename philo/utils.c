/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 16:51:05 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:35:05 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_int(t_table *table)
{
	struct timeval	current_time;
	long			n;

	gettimeofday(&current_time, NULL);
	current_time.tv_sec = current_time.tv_sec - table->start_time.tv_sec;
	current_time.tv_usec = current_time.tv_usec - table->start_time.tv_usec;
	n = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (n);
}

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

void	forks_unlock(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->ph_num)
	{
		pthread_mutex_unlock(&table->forks[i]);
		i++;
	}
}

int	count_meals(t_table *table)
{
	int				i;
	t_philo			*philo;

	i = 0;
	while (i < table->ph_num)
	{
		philo = &table->philos[i];
		if (table->philos[i].num_meals != table->num_eat)
			return (1);
		i++;
	}
	return (0);
}
