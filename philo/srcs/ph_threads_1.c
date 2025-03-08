/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:35:14 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/08 21:12:55 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void set_philosopher_position(t_inputs *phs, t_thread_vars *thread_vars)
// {
// 	thread_vars->i = 0; // Initialize the index

// 	// Find an available philosopher position
// 	while (thread_vars->i < phs->n_philos)
// 	{
// 		if (!*(phs->ph_pos + thread_vars->i)) // Check if the position is available
// 		{
// 			*(phs->ph_pos + thread_vars->i) = 1; // Mark the position as taken
// 			break;
// 		}
// 		thread_vars->i++; // Move to the next position
// 	}

// 	thread_vars->pos = thread_vars->i; // Set the philosopher's position
// }

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

// void    *two_philos(void *arg)
// {
// 	t_inputs *phs = (t_inputs *)arg;
// 	t_thread_vars thread_vars; // Declare a struct variable

// 	// Initialize struct members
// 	thread_vars.flag = 0;

// 	// Set the philosopher's position
// 	set_philosopher_position(phs, &thread_vars);

// 	// Initialize time variables
// 	gettimeofday(&thread_vars.init_time, NULL);
// 	thread_vars.i = 0; // Reset i for the next loop

// 	// Set the queue for the philosopher
// 	// mutex queue to change it and unlock it
// 	pthread_mutex_lock(phs->queue);
// 	ph_set_queue(phs, thread_vars.pos);
// 	pthread_mutex_unlock(phs->queue);

// 	// Main loop for eating and sleeping
// 	while (thread_vars.i < phs->num_eat)
// 	{
// 		// Wait for forks to become available
// 		wait_for_forks(phs, &thread_vars);

// 		// Check if a philosopher has died
// 		if (phs->is_dead)
// 		{
// 			printf("Philosopher died %d\n", thread_vars.pos);
// 			return NULL;
// 		}

// 		// Lock the forks
// 		lock_forks(phs, &thread_vars, LOCKED);

// 		// Get the current time
// 		gettimeofday(&thread_vars.time, NULL);

// 		// Check if the philosopher has starved
// 		if ((!thread_vars.flag && return_time_ms(thread_vars.init_time, thread_vars.time) > phs->ttd / 1000) ||
// 			(thread_vars.flag && return_time_ms(thread_vars.prev_time, thread_vars.time) > phs->ttd / 1000))
// 		{
// 			// Unlock the forks before exiting
// 			lock_forks(phs, &thread_vars, UNLOCKED);
// 			phs->is_dead = 1;
// 			printf("Philosopher died %d\n", thread_vars.pos);
// 			return NULL;
// 		}

// 		// Philosopher takes a fork
// 		printf("%04ld %d has taken a fork\n", return_time_ms(thread_vars.init_time, thread_vars.time), thread_vars.pos + 1);

// 		// Philosopher eats
// 		gettimeofday(&thread_vars.time, NULL);
// 		printf("%ld %d is eating\n", return_time_ms(thread_vars.init_time, thread_vars.time), thread_vars.pos + 1);
// 		usleep(phs->tte);

// 		// Philosopher sleeps
// 		gettimeofday(&thread_vars.prev_time, NULL);
// 		printf("%ld %d is sleeping\n", return_time_ms(thread_vars.init_time, thread_vars.prev_time), thread_vars.pos + 1);

// 		// Unlock the forks
// 		lock_forks(phs, &thread_vars, UNLOCKED);

// 		// Sleep for the specified time
// 		usleep(phs->tts);

// 		// Increment the eating counter if necessary
// 		if (phs->is_num_eat)
// 			thread_vars.i++;

// 		thread_vars.flag = 1; // Set the flag to indicate the philosopher has eaten at least once
// 	}

// 	return NULL;
// }


