/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 21:09:40 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:39:20 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_forks(t_philo *philo)
{
	if ((philo->index + 1) % 2)
	{
		sem_wait(philo->table->forks);
		message(philo, RFORK);
		sem_wait(philo->table->forks);
		message(philo, LFORK);
	}
	else
	{
		sem_wait(philo->table->forks);
		message(philo, LFORK);
		sem_wait(philo->table->forks);
		message(philo, RFORK);
	}
}

void	sleep_clean_thread(t_philo *philo)
{
	message(philo, SLEEP);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	my_sleep(philo->table->time_to_sleep);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->mutex);
	philo->is_eating = 1;
	philo->last_meal = get_time();
	philo->limit = philo->last_meal + philo->table->time_to_die;
	message(philo, EAT);
	my_sleep(philo->table->time_to_eat);
	philo->num_meals++;
	philo->is_eating = 0;
	sem_post(philo->mutex);
	sem_post(philo->eat_count_s);
}

int	cycle(t_philo *philo_v)
{
	t_philo		*philo;
	pthread_t	checker;

	philo = (t_philo *)philo_v;
	philo->last_meal = get_time();
	philo->limit = philo->last_meal + philo->table->time_to_die;
	if (pthread_create(&checker, NULL, &monitor, philo) != 0)
		return (1);
	pthread_detach(checker);
	while (1)
	{
		give_forks(philo);
		eat(philo);
		sleep_clean_thread(philo);
		message(philo, THINK);
	}
	return (0);
}
