/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:13:56 by lorey             #+#    #+#             */
/*   Updated: 2025/01/06 17:26:05 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	errwr(char *text)
{
	write(1, text, ft_strlen(text));
	return (-1);
}

static int	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (0);
	else if (status == EAGAIN)
		return (errwr("No ressources to create another thread"));
	else if (status == EPERM)
		return (errwr("The caller does not have appropriate permission"));
	else if (status == EINVAL && opcode == CREATE)
		return (errwr("The value specified by attr is invalid."));
	else if (status == EINVAL && opcode == JOIN || opcode == DETACH)
		return (errwr("The value specified by thread is not joinable"));
	else if (status == ESRCH)
		return (errwr("No thread with the ID thread could be found."));
	else if (status == EDEADLK)
		return (errwr("A deadlock was detected or the value of... zzzz''"));
	return (0);
}

int	safe_thread_handle(pthread_t *thread, void *(*fun)(void *), void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		return (handle_thread_error(pthread_create(thread, NULL, fun, data), opcode));
	else if (opcode == JOIN)
		return (handle_thread_error(pthread_join(*thread, NULL), opcode));
	else if (opcode == DETACH)
		return (handle_thread_error(pthread_detach(*thread), opcode));
	else
		return (errwr("wrong output for thread handle (CREATE, JOIN, DETACH)"));

}

static int	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (0);
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		return (errwr("The value specified by mutex is invalid."));
	else if (status == EINVAL && opcode == INIT)
		return (errwr("The value specified by attr is invalid."));
	else if (status == EDEADLK)
		return (errwr("A deadlock would occur \
if the thread blocked waiting for mutex"));
	else if (status == EPERM)
		return (errwr("The current thread does not hold a lock on mutex"));
	else if (status == ENOMEM)
		return (errwr("The process cannot allocate enough memory\
to create another mutex"));
	else if (status == EBUSY)
		return (errwr("Mutex is locked"));
	return (0);
}

int	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		return (handle_mutex_error(pthread_mutex_lock(mutex), opcode));
	else if (opcode == UNLOCK)
		return (handle_mutex_error(pthread_mutex_unlock(mutex), opcode));
	else if (opcode == INIT)
		return (handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode));
	else if (opcode == DESTROY)
		return (handle_mutex_error(pthread_mutex_destroy(mutex), opcode));
	else
		return (errwr("Wrong opcode for mutex handle (LOCK, UNLOCK, INIT)"));
}

int	safe_malloc(void *pointer, size_t bytes)
{
	pointer = malloc(bytes);
	if (!pointer)
		return (-1);
	return (0);
}

int	init_data(t_data *data)
{
	data->end_simulation = false;
	if (safe_malloc(data->philos, sizeof(data->philos) * data->philo_nbr))
		return (-1);
	return (0);
}
