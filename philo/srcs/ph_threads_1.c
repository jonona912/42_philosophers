/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:35:14 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/08 21:14:40 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void wait_for_forks(t_inputs *phs, t_thread_vars *thread_vars)
{
	while (1)
	{
		// Check if the philosopher is at position 0 and is next in the queue
		if (thread_vars->pos == 0 && phs->n_philos > 1 && thread_vars->pos == phs->queue[thread_vars->pos][0])
		{
			// Check if the right and left forks are available
			if (!*(phs->is_muted + thread_vars->pos) && !*(phs->is_muted + phs->n_philos - 1))
			{
				ph_remove_first_queue(phs, thread_vars); // Remove from the queue
				break; // Exit the loop
			}
		}
		// Check if the philosopher is next in the queue
		else if (thread_vars->pos == phs->queue[thread_vars->pos][0])
		{
			// Check if the right and left forks are available
			if (!*(phs->is_muted + thread_vars->pos) && !*(phs->is_muted + thread_vars->pos - 1))
			{
				ph_remove_first_queue(phs, thread_vars); // Remove from the queue
				break; // Exit the loop
			}
		}
	}
}

void lock_forks(t_inputs *phs, t_thread_vars *thread_vars, t_lock_status status)
{
	int fork_status = (status == LOCKED) ? 1 : 0; // Set fork_status based on the enum

	// Update the right fork
	*(phs->is_muted + thread_vars->pos) = fork_status;

	// Update the left fork based on the philosopher's position
	if (thread_vars->pos == 0)
	{
		*(phs->is_muted + thread_vars->pos) = fork_status;
		if (status == LOCKED)
			pthread_mutex_lock(phs->forks + phs->n_philos - 1); // Lock left fork for the first philosopher
		else
			pthread_mutex_unlock(phs->forks + phs->n_philos - 1); // Unlock left fork for the first philosopher
	}
	else
	{
		*(phs->is_muted + thread_vars->pos - 1) = fork_status;
		if (status == LOCKED)
			pthread_mutex_lock(phs->forks + thread_vars->pos - 1); // Lock left fork for other philosophers
		else
			pthread_mutex_unlock(phs->forks + thread_vars->pos - 1); // Unlock left fork for other philosophers
	}

	// Update the right fork's mutex
	if (status == LOCKED)
		pthread_mutex_lock(phs->forks + thread_vars->pos); // Lock right fork
	else
		pthread_mutex_unlock(phs->forks + thread_vars->pos); // Unlock right fork
}
