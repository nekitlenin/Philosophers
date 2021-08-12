/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 00:40:33 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:29:02 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char
	*message_2(int cont)
{
	if (cont == EAT)
		return (" is eating\n");
	else if (cont == SLEEP)
		return (" is sleeping\n");
	else if (cont == RFORK)
		return (" has taken right fork\n");
	else if (cont == LFORK)
		return (" has taken left fork\n");
	else if (cont == THINK)
		return (" is thinking\n");
	else if (cont == DONE)
		return ("\x1b[32mphilosophers finished their dinner\x1b[0m\n");
	return ("\x1b[31m DIED\x1b[0m\n");
}

void	message(t_philo *philo, int cont)
{
	sem_wait(philo->table->write);
	sem_wait(philo->table->deadwr);
	ft_putnbr_fd(get_time() - philo->table->start, 1, 1);
	write(1, "\t", 1);
	if (cont != DONE)
		ft_putnbr_fd(philo->index + 1, 1, 0);
	write(1, message_2(cont), ft_strlen(message_2(cont)));
	if (cont < DIED)
		sem_post(philo->table->deadwr);
	sem_post(philo->table->write);
}
