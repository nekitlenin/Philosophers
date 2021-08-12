/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 16:52:23 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:29:05 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			i = -1;
			break ;
		}
		i++;
	}
	if (i == -1)
		return (-1);
	return (0);
}

int	wrong_input(char *err)
{
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	return (-1);
}

int	parse_philo_utils_2(t_table *table, t_arg *arg)
{
	int	n;

	if (arg->argc == 6)
	{
		n = ft_atoi(arg->argv[5]);
		if (n > 0)
			table->num_eat = n;
		else
			return (wrong_input("error: wrong parameters"));
	}
	else if (arg->argc == 5)
		table->num_eat = 0;
	return (0);
}

int	parse_philo_utils(t_table *table, t_arg *arg)
{
	int	n;

	n = ft_atoi(arg->argv[1]);
	if (n > 0)
		table->ph_num = n;
	else
		return (wrong_input("error: wrong parameters"));
	n = ft_atoi(arg->argv[2]);
	if (n > 59)
		table->time_to_die = n;
	else
		return (wrong_input("error: wrong parameters"));
	n = ft_atoi(arg->argv[3]);
	if (n > 59)
		table->time_to_eat = n;
	else
		return (wrong_input("error: wrong parameters"));
	n = ft_atoi(arg->argv[4]);
	if (n > 59)
		table->time_to_sleep = n;
	else
		return (wrong_input("error: wrong parameters"));
	if (parse_philo_utils_2(table, arg) != 0)
		return (1);
	return (0);
}

int	parse_philo(t_table *table, t_arg *arg)
{
	int	i;

	i = 1;
	if (arg->argc < 5 || arg->argc > 6)
		return (wrong_input("error: wrong number of argumnets"));
	while (i < arg->argc)
	{
		if (check_args(arg->argv[i]) == 0)
		{
			i++;
			continue ;
		}
		return (wrong_input("error: wrong parameters"));
	}
	if (parse_philo_utils(table, arg) != 0)
		return (-1);
	return (0);
}
