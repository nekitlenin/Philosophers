/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:46:24 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:29:43 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*ft_sem_open(char const *name, int value)
{
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

char	*sem_create_name(char const *base, char *buffer, int position)
{
	int	i;

	i = ft_strcpy(buffer, base);
	while (position > 0)
	{
		buffer[i++] = (position % 10) + '0';
		position /= 10;
	}
	buffer[i] = 0;
	return (buffer);
}

static int	init_sem(t_table *table)
{
	sem_unlink("sem_fork");
	sem_unlink("sem_write");
	sem_unlink("sem_death");
	sem_unlink("sem_deathwr");
	table->forks = ft_sem_open("sem_fork", table->ph_num);
	table->write = ft_sem_open("sem_write", 1);
	table->death = ft_sem_open("sem_death", 0);
	table->deadwr = ft_sem_open("sem_deathwr", 1);
	if (table->forks < 0 || table->write < 0
		|| table->death < 0 || table->deadwr < 0)
		return (1);
	return (0);
}

static int	init_philo(t_table *table)
{
	int		i;
	char	semaphore[250];

	i = 0;
	while (i < table->ph_num)
	{
		table->philos[i].is_eating = 0;
		table->philos[i].index = i;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->ph_num;
		table->philos[i].table = table;
		sem_create_name("sem_ph", (char *)semaphore, i);
		sem_unlink(semaphore);
		table->philos[i].mutex = ft_sem_open(semaphore, 1);
		if (table->philos[i].mutex < 0)
			return (1);
		sem_create_name("sem_meal", (char *)semaphore, i);
		sem_unlink(semaphore);
		table->philos[i].eat_count_s = ft_sem_open(semaphore, 0);
		if (table->philos[i].eat_count_s < 0)
			return (1);
		i++;
	}
	return (0);
}

int	prepare_table(t_table *table, struct timeval start, t_arg *arg)
{
	table->start_time = start;
	if (parse_philo(table, arg) == -1)
		return (-1);
	table->forks = NULL;
	table->philos = NULL;
	table->philos = (t_philo *)malloc(sizeof(*(table->philos)) * table->ph_num);
	if (!table->philos)
		return (1);
	if (init_sem(table))
		return (1);
	if (init_philo(table))
		return (1);
	return (0);
}
