/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:33:16 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:39:54 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define EAT 	0
# define SLEEP	1
# define RFORK	2
# define LFORK	3
# define THINK	4
# define DIED 	5
# define DONE 	6

typedef struct s_arg {
	char			**argv;
	int				argc;
}					t_arg;

typedef struct s_philo {
	char		*name;
	int			left_fork;
	int			right_fork;
	int			limit;
	int			last_meal;
	int			num_meals;
	int			index;
}				t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	t_philo			*philos;

	int				ph_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				num_eat;
	int				allowed;
	struct timeval	start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
}					t_table;

typedef struct s_philo_struct {
	t_philo			*philosopher;
	t_table			*table;
}					t_philo_struct;

int		ft_isdigit(int c);
int		ft_strlen(const char *str);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
void	init_philo(t_philo *philosopher, char *name,
			unsigned left_fork, unsigned right_fork);
void	call_philo(t_philo *philosophers, t_table *table);
int		prepare_table(t_table *table, struct timeval start, t_arg *arg);
int		check_args(char *arg);
int		wrong_input(char *err);
int		parse_philo(t_table *table, t_arg *arg);
long	get_time_int(t_table *table);
long	get_time(void);
int		my_sleep(int sleep);
void	forks_unlock(t_table *table);
int		count_meals(t_table *table);
int		message(t_table *table, char *philo_name, int cont);
void	*cycle(void *arguments);
int		sleep_thread(t_table *table, t_philo *philo);
int		eat(t_table *table, t_philo *philo);
void	give_forks(t_philo *philo, t_table *table);
void	*monitor(void *arg);

#endif