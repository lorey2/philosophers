/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:30:40 by lorey             #+#    #+#             */
/*   Updated: 2025/04/16 19:52:20 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	all_threads_running(t_mtx *mutex, long *threads,
			long philo_nbr, t_data *data)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK, data);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK, data);
	return (ret);
}

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->data_mutex, &data->all_threads_ready, data))
		;
}
