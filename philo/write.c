/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:18:36 by lorey             #+#    #+#             */
/*   Updated: 2025/04/16 19:41:42 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->data))
		printf(BR_WH"%12ld"RST" %d has taken the first fork"
			"\t\t\t\tn⚬"BRIGHT_BLUE"[ %d ]\n"RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->data))
		printf(BR_WH"%12ld"RST" %d has taken the second fork"
			"\t\t\tn⚬"BRIGHT_BLUE"[ %d ]\n"RST, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (status == SLEEPING && !simulation_finished(philo->data))
		printf(BR_WH"%12ld"RST" %d is sleeping\n", elapsed, philo->id);
	else if (status == EATING && !simulation_finished(philo->data))
		printf(BRIGHT_GREEN"%12ld"RST" %d is eating"
			"\t\t\t"YELLOW"[ %ld ]\n", elapsed, philo->id, philo->meals_counter);
	else if (status == THINKING && !simulation_finished(philo->data))
		printf(BR_WH"%12ld"RST" %d is thinking\n", elapsed, philo->id);
	else if (status == DIED && !simulation_finished(philo->data))
		printf(BR_WH"%12ld"RST" %d has died\n", elapsed, philo->id);
}

void	write_status(t_philo_status status,
					t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILISECOND) - philo->data->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->data->write_mutex, LOCK, philo->data);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_SECOND_FORK || status == TAKE_FIRST_FORK) \
			&& !simulation_finished(philo->data))
			printf(BR_WH"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		if (status == SLEEPING && !simulation_finished(philo->data))
			printf(BR_WH"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		if (status == EATING && !simulation_finished(philo->data))
			printf(BR_WH"%-6ld"RST" %d is eating\n", elapsed, philo->id);
		if (status == THINKING && !simulation_finished(philo->data))
			printf(BR_WH"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		if (status == DIED && !simulation_finished(philo->data))
			printf(BR_WH"%-6ld"RST" %d has died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->data->write_mutex, UNLOCK, philo->data);
}
