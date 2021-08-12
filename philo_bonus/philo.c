/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:46:01 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:28:55 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philo(t_table *table, t_arg *arg)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	if (prepare_table(table, start_time, arg) == -1)
		return (-1);
	return (0);
}

static int	main_threads(t_table *table)
{
	int			i;
	void		*philo;

	table->start = get_time();
	i = 0;
	while (i < table->ph_num)
	{
		philo = (void *)(&table->philos[i]);
		table->philos[i].pid = fork();
		if (table->philos[i].pid < 0)
			return (1);
		else if (table->philos[i].pid == 0)
		{
			cycle(&table->philos[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	return (0);
}

int	free_philos(t_table *table)
{
	int		i;
	char	semaphore[255];

	sem_unlink("sem_fork");
	sem_unlink("sem_write");
	sem_unlink("sem_death");
	sem_unlink("sem_deathwr");
	if (table->philos)
	{
		i = 0;
		while (i < table->ph_num)
		{
			sem_create_name("sem_ph", (char *)semaphore, i);
			sem_unlink(semaphore);
			sem_create_name("sem_meal", (char *)semaphore, i++);
			sem_unlink(semaphore);
		}
		free(table->philos);
	}
	return (1);
}

int
	main(int argc, char **argv)
{
	int				i;
	t_philo_struct	*args;
	t_table			table;
	t_arg			arg;

	arg.argc = argc;
	arg.argv = argv;
	if (start_philo(&table, &arg) == -1)
		return (-1);
	args = malloc(sizeof(t_philo_struct) * table.ph_num);
	if (!args)
		return (1);
	if (start_monitor_thread(&table)
		|| main_threads(&table))
		return (free_philos(&table) && wrong_input("error: fatal\n"));
	sem_wait(table.death);
	i = 0;
	while (i < table.ph_num)
		kill(table.philos[i++].pid, SIGKILL);
	free_philos(&table);
	return (0);
}
