/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 16:50:30 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:45:01 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	message_2(t_table *table, char *philo_name, int cont)
{
	if ((cont == DIED) && (table->allowed == 1))
	{
		printf("[%ld]\x1b[31m	%s DIED\x1b[0m\n",
			get_time_int(table), philo_name);
		pthread_mutex_unlock(&table->write);
		return (0);
	}
	if ((cont == DONE) && (table->allowed == 1))
	{
		printf("[%ld]\x1b[32m	philosophers finished their dinner\x1b[0m\n",
			get_time_int(table));
		pthread_mutex_unlock(&table->write);
		return (0);
	}
	return (1);
}

int	message(t_table *table, char *philo_name, int cont)
{
	if (table->allowed == 1)
	{
		pthread_mutex_lock(&table->write);
		if ((cont == LFORK) && (table->allowed == 1))
			printf("[%ld]	%s has taken left fork\n",
				get_time_int(table), philo_name);
		else if ((cont == RFORK) && (table->allowed == 1))
			printf("[%ld]	%s has taken right fork\n",
				get_time_int(table), philo_name);
		else if ((cont == EAT) && (table->allowed == 1))
			printf("[%ld]	%s is eating\n", get_time_int(table), philo_name);
		else if ((cont == SLEEP) && (table->allowed == 1))
			printf("[%ld]	%s is sleeping\n", get_time_int(table), philo_name);
		else if ((cont == THINK) && (table->allowed == 1))
			printf("[%ld]	%s is thinking\n", get_time_int(table), philo_name);
		else if (message_2(table, philo_name, cont) == 0
			&& (table->allowed == 1))
			return (0);
		pthread_mutex_unlock(&table->write);
		return (1);
	}
	else
		return (0);
}
