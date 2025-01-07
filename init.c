/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:13:56 by lorey             #+#    #+#             */
/*   Updated: 2025/01/07 14:52:48 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int	errwr(char *text)
{
	write(1, text, ft_strlen(text));
	return (-1);
}

int	safe_malloc(void **pointer, size_t bytes)
{
	*pointer = malloc(bytes);
	if (!*pointer)
		errwr("malloc returned null (how did you do that)");
	return (0);
}

//care for deadlock here

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	if (philo->id % 2)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &forks[(position + 1) % philo_nbr];
		philo->second_fork = &forks[position];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_nbr)
	{
		write(1, "salut", 5);
		philo = data->philos + i;
		philo->full = false;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->data = data;
		assign_forks(philo, data->forks, i);
	}
}

int	init_data(t_data *data)
{
	int	i;

	i = -1;
	data->end_simulation = false;
	if (safe_malloc((void **)&data->philos, sizeof(t_philo) * data->philo_nbr))
		return (-1);
	if (safe_malloc((void **)&data->forks, sizeof(t_fork) * data->philo_nbr))
		return (-1);
	while (++i < data->philo_nbr)
	{
		safe_mutex_handle(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	philo_init(data);
	return (0);
}
