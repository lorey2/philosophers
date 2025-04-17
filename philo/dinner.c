/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:44:24 by lorey             #+#    #+#             */
/*   Updated: 2025/04/16 19:53:43 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

static void	*lone_philo(void *data_void)
{
	t_philo	*philo;

	philo = (t_philo *)data_void;
	set_long(&philo->pilo_mutex, &philo->last_meal_time,
		get_time(MILISECOND), philo->data);
	increase_long(&philo->data->data_mutex,
		&philo->data->threads_running_nbr, philo->data);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->data))
		usleep(200);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK, philo->data);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK, philo->data);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->pilo_mutex, &philo->last_meal_time,
		get_time(MILISECOND), philo->data);
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->nbr_limit_meals <= philo->meals_counter
		&& philo->data->nbr_limit_meals > 0)
		set_bool(&philo->pilo_mutex, &philo->full, true, philo->data);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK, philo->data);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK, philo->data);
}

void	*dinner_simulation(void *p_data)
{
	t_philo	*philo;

	philo = (t_philo *)p_data;
	wait_all_threads(philo->data);
	set_long(&philo->pilo_mutex, &philo->last_meal_time,
		get_time(MILISECOND), philo->data);
	increase_long(&philo->data->data_mutex,
		&philo->data->threads_running_nbr, philo->data);
	while (simulation_finished(philo->data) == false)
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	if (data->nbr_limit_meals == 0)
		return ;
	else if (data->philo_nbr == 1)
		safe_thread_handle(&data->philos[0].thread_id,
			lone_philo, &data->philos[0], CREATE);
	else
	{
		while (++i < data->philo_nbr)
			safe_thread_handle(&data->philos[i].thread_id, \
				dinner_simulation, &data->philos[i], CREATE);
	}
	safe_thread_handle(&data->monitor, monitor_dinner, data, CREATE);
	set_bool(&data->data_mutex, &data->all_threads_ready, true, data);
	i = -1;
	while (++i < data->philo_nbr)
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&data->data_mutex, &data->end_simulation, true, data);
	safe_thread_handle(&data->monitor, NULL, NULL, JOIN);
}
