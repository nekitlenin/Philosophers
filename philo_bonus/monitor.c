/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:46:08 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:29:04 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*count_meals(void *table_v)
{
	t_table	*table;
	int		total;
	int		i;

	table = (t_table *)table_v;
	total = 0;
	while (total < table->num_eat)
	{
		i = 0;
		while (i < table->ph_num)
			sem_wait(table->philos[i++].eat_count_s);
		total++;
	}
	message(&table->philos[0], DONE);
	sem_post(table->death);
	return ((void *)0);
}

void	*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		sem_wait(philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			message(philo, DIED);
			sem_post(philo->mutex);
			sem_post(philo->table->death);
			return ((void *)0);
		}
		sem_post(philo->mutex);
		usleep(50);
	}
	return ((void *)0);
}

int	start_monitor_thread(t_table *table)
{
	pthread_t	checker;

	if (table->num_eat > 0)
	{
		if (pthread_create(&checker, NULL, &count_meals, (void *)table) != 0)
			return (1);
		pthread_detach(checker);
	}
	return (0);
}
