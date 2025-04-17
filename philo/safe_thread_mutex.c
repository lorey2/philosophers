/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_thread_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:49:00 by lorey             #+#    #+#             */
/*   Updated: 2025/04/16 19:54:40 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	handle_thread_error(int status, t_opcode opcode, t_data *data)
{
	if (status == 0)
		return ;
	else if (status == EAGAIN)
		error("No ressources to create another thread", data);
	else if (status == EPERM)
		error("The caller does not have appropriate permission", data);
	else if (status == EINVAL && opcode == CREATE)
		error("The value specified by attr is invalid.", data);
	else if ((status == EINVAL && opcode == JOIN) || opcode == DETACH)
		error("The value specified by thread is not joinable", data);
	else if (status == ESRCH)
		error("No thread with the ID thread could be found.", data);
	else if (status == EDEADLK)
		error("A deadlock was detected or the value of... zzzz''", data);
}

void	safe_thread_handle(pthread_t *thread, \
	void *(*fun)(void *), void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, fun, data),
			opcode, data);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode, data);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode, data);
	else
		error("wrong output for thread handle (CREATE, JOIN, DETACH)", data);
}

static void	handle_mutex_error(int status, t_opcode opcode, t_data *data)
{
	if (status == 0)
		return ;
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error("The value specified by mutex is invalid.", data);
	else if (status == EINVAL && opcode == INIT)
		error("The value specified by attr is invalid.", data);
	else if (status == EDEADLK)
		error("A deadlock would occur \
if the thread blocked waiting for mutex", data);
	else if (status == EPERM)
		error("The current thread does not hold a lock on mutex", data);
	else if (status == ENOMEM)
		error("The process cannot allocate enough memory\
to create another mutex", data);
	else if (status == EBUSY)
		error("Mutex is locked", data);
	return ;
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode, t_data *data)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode, data);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode, data);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode, data);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode, data);
	else
		error("Wrong opcode for mutex handle (LOCK, UNLOCK, INIT)", data);
}
