/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 16:49:45 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:39:54 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_forks(t_philo *philo, t_table *table)
{
	if ((philo->index + 1) % 2)
	{
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		message(table, philo->name, RFORK);
		message(table, philo->name, LFORK);
	}
	else
	{
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		message(table, philo->name, LFORK);
		message(table, philo->name, RFORK);
	}
}

int	eat(t_table *table, t_philo *philo)
{
	message(table, philo->name, EAT);
	philo->limit = get_time_int(table) + table->time_to_die;
	my_sleep(table->time_to_eat);
	if (table->num_eat != 0)
		philo->num_meals += 1;
	if (table->num_eat != 0)
	{
		if (count_meals(table) == 0)
		{
			message(table, philo->name, DONE);
			table->allowed = 0;
			forks_unlock(table);
			return (1);
		}
	}
	return (0);
}

int	sleep_thread(t_table *table, t_philo *philo)
{
	message(table, philo->name, SLEEP);
	my_sleep(table->time_to_sleep);
	return (0);
}

void	*cycle(void *arguments)
{
	t_philo			*philo;
	t_philo_struct	*arg;
	t_table			*table;

	arg = (t_philo_struct *)arguments;
	table = arg->table;
	arg->philosopher->limit = get_time_int(arg->table) + table->time_to_die;
	while (table->allowed)
	{
		philo = arg->philosopher;
		give_forks(philo, table);
		if (eat(table, philo) != 0)
			break ;
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
		if (sleep_thread(table, philo) != 0)
			break ;
		message(table, philo->name, THINK);
	}
	return ((void *)0);
}
