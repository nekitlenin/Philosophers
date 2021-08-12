/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:32:52 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:39:20 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

# define EAT 	0
# define SLEEP	1
# define RFORK	2
# define LFORK	3
# define THINK	4
# define DIED 	5
# define DONE 	6

struct	s_table;

typedef struct s_arg {
	char			**argv;
	int				argc;
}					t_arg;

typedef struct s_philo
{
	pid_t			pid;
	int				index;
	int				is_eating;
	long			limit;
	long			last_meal;
	int				left_fork;
	int				right_fork;
	struct s_table	*table;
	int				num_meals;
	sem_t			*mutex;
	sem_t			*eat_count_s;
}					t_philo;

typedef struct s_table
{
	sem_t			*forks;
	t_philo			*philos;
	int				ph_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_eat;
	long			start;
	struct timeval	start_time;
	sem_t			*write;
	sem_t			*death;
	sem_t			*deadwr;
}					t_table;

typedef struct s_philo_struct {
	t_philo			*philosopher;
	t_table			*table;
}					t_philo_struct;

int					ft_strncmp(const char *s1, const char *s2);
int					wrong_input(char *err);
int					ft_isdigit(int a);
int					parse_philo(t_table *table, t_arg *arg);
int					my_sleep(int sleep);
int					cycle(t_philo *philo_v);
int					ft_strlen(char const *str);
int					ft_atoi(char const *str);
void				ft_putnbr_fd(long n, int fd, int mod);
int					ft_strcpy(char *dst, const char *src);
long				get_time(void);
int					free_philos(t_table *table);
int					prepare_table(t_table *table,
						struct timeval start, t_arg *arg);
char				*sem_create_name(char const *base,
						char *buffer, int position);
void				*count_meals(void *table_v);
void				*monitor(void *philo_v);
int					start_monitor_thread(t_table *table);
void				give_forks(t_philo *philo);
void				sleep_clean_thread(t_philo *philo);
void				message(t_philo *philo, int cont);

#endif
