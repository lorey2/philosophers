/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:11:53 by lorey             #+#    #+#             */
/*   Updated: 2025/04/16 20:28:33 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define BLACK   "\033[0;30m"
# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN    "\033[0;36m"
# define WHITE   "\033[0;37m"

# define BRIGHT_BLACK   "\033[0;90m"
# define BRIGHT_RED     "\033[0;91m"
# define BRIGHT_GREEN   "\033[0;92m"
# define BRIGHT_YELLOW  "\033[0;93m"
# define BRIGHT_BLUE    "\033[0;94m"
# define BRIGHT_MAGENTA "\033[0;95m"
# define BRIGHT_CYAN    "\033[0;96m"
# define BR_WH   "\033[0;97m"

# define RST   "\033[0m"

# define DEBUG_MODE 0

typedef pthread_mutex_t	t_mtx;
typedef struct timeval	t_tv;

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

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}			t_time_code;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long long	last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		pilo_mutex;
	t_data		*data;
}			t_philo;

struct s_data
{
	bool		error;
	int			philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			nbr_limit_meals;
	long long	start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		data_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
};

long long	ft_atoi(const char *str);
size_t		ft_strlen_skip_zero(const char *s);
size_t		ft_strlen(const char *s);
void		error(char *text, t_data *data);
void		precise_usleep(long usec, t_data *data);
void		safe_mutex_handle(t_mtx *mutex, t_opcode opcode, t_data *data);
void		safe_thread_handle(pthread_t *thread, \
			void *(*fun)(void *), void *data, t_opcode opcode);
void		safe_malloc(void **pointer, size_t bytes, t_data *data);
int			init_data(t_data *data);
char		*ft_itoa(int nbr);
void		set_bool(t_mtx *mutex, bool *dest, bool value, t_data *data);
bool		get_bool(t_mtx *mutex, bool *value, t_data *data);
void		set_long(t_mtx *mutex, long long *dest,
				long long value, t_data *data);
long long	get_long(t_mtx *mutex, long long *value, t_data *data);
void		increase_long(t_mtx *mutex, long *dest, t_data *data);
bool		simulation_finished(t_data *data);
void		wait_all_threads(t_data *data);
long long	get_time(t_time_code time_code);
void		write_status(t_philo_status status,
				t_philo *philo, bool debug);
void		dinner_start(t_data *data);
bool		all_threads_running(t_mtx *mutex, long *threads,
				long philo_nbr, t_data *data);
void		*monitor_dinner(void *data_void);
void		clean(t_data *data);

#endif
