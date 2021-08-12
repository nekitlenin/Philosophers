/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 16:49:59 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:34:01 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philosopher, char *name,
						unsigned left_fork, unsigned right_fork)
{
	philosopher->name = name;
	philosopher->left_fork = left_fork;
	philosopher->right_fork = right_fork;
	philosopher->limit = 0;
	philosopher->last_meal = 0;
	philosopher->num_meals = 0;
}

void	call_philo(t_philo *philosophers, t_table *table)
{
	int		i;
	char	*name;

	i = 0;
	while (i < table->ph_num - 1)
	{
		name = ft_itoa(i + 1);
		init_philo(&philosophers[i], name, i, i + 1);
		i++;
	}
	init_philo(&philosophers[table->ph_num - 1],
		ft_itoa(table->ph_num), table->ph_num - 1, 0);
}

int	prepare_table(t_table *table, struct timeval start, t_arg *arg)
{
	int	i;

	i = 0;
	if (parse_philo(table, arg) == -1)
		return (-1);
	table->start_time = start;
	pthread_mutex_init(&table->death, NULL);
	pthread_mutex_init(&table->write, NULL);
	table->allowed = 1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->ph_num);
	table->philos = malloc(sizeof(t_philo) * table->ph_num);
	while (i < table->ph_num)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	call_philo(table->philos, table);
	return (0);
}
