/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lorey <loic.rey.vs@gmail.com>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/08 20:43:49 by lorey			 #+#	#+#			 */
/*   Updated: 2025/04/16 20:28:11 by lorey            ###   LAUSANNE.ch       */
/*																			*/
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <unistd.h>

void	error(char *text, t_data *data)
{
	printf("%s", text);
	data->error = true;
}

void	safe_malloc(void **pointer, size_t bytes, t_data *data)
{
	*pointer = malloc(bytes);
	if (!*pointer)
		error("malloc returned null (how did you do that)", data);
}

long long	get_time(t_time_code time_code)
{
	t_tv	tv;

	if (gettimeofday(&tv, NULL) == -1)
		printf("gettimeofday returned -1. New bug in bugdex");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILISECOND)
		return (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return (tv.tv_sec * 1e6 + (tv.tv_usec));
	else
		printf("wrong input in enum time_code in get_time");
	return (42);
}

void	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(data))
			break ;
		rem = usec - get_time(MICROSECOND);
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (get_time(MICROSECOND) - start < usec)
				;
	}
}

void	clean(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philos + i;
		safe_mutex_handle(&philo->pilo_mutex, DESTROY, data);
	}
	safe_mutex_handle(&data->data_mutex, DESTROY, data);
	safe_mutex_handle(&data->write_mutex, DESTROY, data);
	free(data->forks);
	free(data->philos);
}
