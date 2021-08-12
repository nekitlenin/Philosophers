/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 16:50:36 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:33:21 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_table			*table;
	t_philo			*philo;
	int				i;
	int				temp;

	table = (t_table *)arg;
	while (table->allowed)
	{
		i = 0;
		while (i < table->ph_num)
		{
			philo = &table->philos[i];
			temp = get_time_int(table);
			if (temp > philo->limit)
			{
				message(table, philo->name, DIED);
				table->allowed = 0;
				forks_unlock(table);
				return ((void *)0);
			}
			i++;
		}
		usleep(50);
	}
	return ((void *)0);
}
