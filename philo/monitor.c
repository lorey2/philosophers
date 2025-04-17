/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:11:03 by lorey             #+#    #+#             */
/*   Updated: 2025/04/16 19:52:44 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	philo_died(t_philo *philo)
{
	long		elapsed;
	long		t_to_die;

	if (get_bool(&philo->pilo_mutex, &philo->full, philo->data))
		return (false);
	elapsed = get_time(MILISECOND)
		- get_long(&philo->pilo_mutex, &philo->last_meal_time, philo->data);
	t_to_die = philo->data->time_to_die;
	if (elapsed > t_to_die / 1e3 + 4)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data_void)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_void;
	while (!all_threads_running(&data->data_mutex, &data->threads_running_nbr,
			data->philo_nbr, data))
		;
	while (!simulation_finished(data))
	{
		i = -1;
		while (++i < data->philo_nbr && !simulation_finished(data))
		{
			if (philo_died(data->philos + i)
				|| get_bool(&data->data_mutex, &data->error, data))
			{
				write_status(DIED, data->philos + i, DEBUG_MODE);
				set_bool(&data->data_mutex, &data->end_simulation, true, data);
			}
		}
	}
	return (NULL);
}
