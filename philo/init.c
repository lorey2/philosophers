/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:13:56 by lorey             #+#    #+#             */
/*   Updated: 2025/04/16 19:37:59 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//care for deadlock here

bool	simulation_finished(t_data *data)
{
	return (get_bool(&data->data_mutex, &data->end_simulation, data));
}

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->first_fork = &forks[(position + 1) % philo_nbr];
	philo->second_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->full = false;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->data = data;
		philo->last_meal_time = data->start_simulation;
		safe_mutex_handle(&philo->pilo_mutex, INIT, data);
		assign_forks(philo, data->forks, i);
	}
}

int	init_data(t_data *data)
{
	int	i;

	i = -1;
	data->error = false;
	data->threads_running_nbr = 0;
	data->start_simulation = get_time(MILISECOND);
	data->end_simulation = false;
	data->all_threads_ready = false;
	safe_malloc((void **)&data->philos,
		sizeof(t_philo) * data->philo_nbr, data);
	safe_mutex_handle(&data->data_mutex, INIT, data);
	safe_mutex_handle(&data->write_mutex, INIT, data);
	safe_malloc((void **)&data->forks, sizeof(t_fork) * data->philo_nbr, data);
	while (++i < data->philo_nbr)
	{
		safe_mutex_handle(&data->forks[i].fork, INIT, data);
		data->forks[i].fork_id = i;
	}
	philo_init(data);
	return (0);
}
