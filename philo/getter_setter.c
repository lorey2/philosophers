/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:05:48 by lorey             #+#    #+#             */
/*   Updated: 2025/04/16 19:33:42 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdbool.h>

void	set_bool(t_mtx *mutex, bool *dest, bool value, t_data *data)
{
	safe_mutex_handle(mutex, LOCK, data);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK, data);
}

bool	get_bool(t_mtx *mutex, bool *value, t_data *data)
{
	int	ret;

	safe_mutex_handle(mutex, LOCK, data);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK, data);
	return (ret);
}

void	set_long(t_mtx *mutex, long long *dest, long long value, t_data *data)
{
	safe_mutex_handle(mutex, LOCK, data);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK, data);
}

long long	get_long(t_mtx *mutex, long long *value, t_data *data)
{
	long long	ret;

	safe_mutex_handle(mutex, LOCK, data);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK, data);
	return (ret);
}

void	increase_long(t_mtx *mutex, long *dest, t_data *data)
{
	safe_mutex_handle(mutex, LOCK, data);
	(*dest)++;
	safe_mutex_handle(mutex, UNLOCK, data);
}
