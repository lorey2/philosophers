/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:11:53 by lorey             #+#    #+#             */
/*   Updated: 2025/01/06 18:39:23 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

typedef pthread_mutex_t	t_mtx;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	int			meals_counter;
	bool		full;
	int			last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_data		*data;
}			t_philo;

struct s_data
{
	int		philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nbr_limit_meals;
	int		start_simulation;
	int		end_simulation;
	t_fork	*forks;
	t_philo	*philos;
};

long long	ft_atoi(const char *str);
size_t		ft_strlen_skip_zero(const char *s);
size_t		ft_strlen(const char *s);
int			errwr(char *text);
int			safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
int			safe_thread_handle(pthread_t *thread, \
			void *(*fun)(void *), void *data, t_opcode opcode);
int			safe_malloc(void *pointer, size_t bytes);
int			init_data(t_data *data);
char		*ft_itoa(int nbr);

#endif
