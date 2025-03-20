/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:35:14 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/20 23:49:47 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	more_than_one_philo_cycles(t_inputs *phs, t_thread_vars *thread_vars)
{
	while (thread_vars->i < phs->num_eat)
	{
		if (philo_eat_loop(phs, thread_vars, phs->tte) == -1)
			return ;
		ph_unlock_forks(phs, thread_vars);
		ph_set_queue(phs, thread_vars->pos);
		if (philo_sleep_loop(phs, thread_vars, phs->tts) == -1)
			return ;
		if (philo_thinking(phs, thread_vars) == -1)
			return ;
		ph_lock_forks(phs, thread_vars);
		ph_remove_first_queue(phs, thread_vars);
		if (phs->is_num_eat)
			thread_vars->i++;
	}
	ph_unlock_forks(phs, thread_vars);
}

void	*more_than_one_philo(void *arg)
{
	t_inputs		*phs;
	t_thread_vars	thread_vars;

	phs = (t_inputs *)arg;
	initialize_thread_vars(phs, &thread_vars);
	set_philosopher_position(phs, &thread_vars);
	set_philosopher_forks(phs, &thread_vars);
	gettimeofday(&thread_vars.time_ate, NULL);
	gettimeofday(&thread_vars.prev_time, NULL);
	if ((thread_vars.pos + 1) % 2 == 1)
	{
		ph_set_queue(phs, thread_vars.pos);
		if (philo_sleep_loop(phs, &thread_vars, phs->tts) == -1)
			return (NULL);
		if (philo_thinking(phs, &thread_vars) == -1)
			return (NULL);
		ph_lock_forks(phs, &thread_vars);
	}
	else
	{
		ph_lock_forks(phs, &thread_vars);
	}
	more_than_one_philo_cycles(phs, &thread_vars);
	return (NULL);
}

int create_and_join_threads(pthread_t *philos, t_inputs *crit)
{
	int i;

	if (crit->n_philos == 1)
	{
		if (pthread_create(philos, NULL, philosopher_activity, crit) != 0)
			return (-1);
		if (pthread_join(*philos, NULL) != 0)
			return (-1);
	}
	else
	{
		i = 0;
		while (i < crit->n_philos)
		{
			if (pthread_create((philos + i), NULL, more_than_one_philo, crit) != 0)
				return (-1);
			i++;
		}
		i = 0;
		while (i < crit->n_philos)
		{
			if (pthread_join(*(philos + i), NULL) != 0)
				return (-1);
			i++;
		}
	}
	return (0);
}










// void wait_for_forks(t_inputs *phs, t_thread_vars *thread_vars)
// {
// 	while (1)
// 	{
// 		// Check if the philosopher is at position 0 and is next in the queue
// 		if (thread_vars->pos == 0 && phs->n_philos > 1 && thread_vars->pos == phs->queue[thread_vars->pos][0])
// 		{
// 			// Check if the right and left forks are available
// 			if (!*(phs->is_muted + thread_vars->pos) && !*(phs->is_muted + phs->n_philos - 1))
// 			{
// 				ph_remove_first_queue(phs, thread_vars); // Remove from the queue
// 				break; // Exit the loop
// 			}
// 		}
// 		// Check if the philosopher is next in the queue
// 		else if (thread_vars->pos == phs->queue[thread_vars->pos][0])
// 		{
// 			// Check if the right and left forks are available
// 			if (!*(phs->is_muted + thread_vars->pos) && !*(phs->is_muted + thread_vars->pos - 1))
// 			{
// 				ph_remove_first_queue(phs, thread_vars); // Remove from the queue
// 				break; // Exit the loop
// 			}
// 		}
// 	}
// }

// void lock_forks(t_inputs *phs, t_thread_vars *thread_vars, t_lock_status status)
// {
// 	int fork_status = (status == LOCKED) ? 1 : 0; // Set fork_status based on the enum

// 	// Update the right fork
// 	*(phs->is_muted + thread_vars->pos) = fork_status;

// 	// Update the left fork based on the philosopher's position
// 	if (thread_vars->pos == 0)
// 	{
// 		*(phs->is_muted + thread_vars->pos) = fork_status;
// 		if (status == LOCKED)
// 			pthread_mutex_lock(phs->forks + phs->n_philos - 1); // Lock left fork for the first philosopher
// 		else
// 			pthread_mutex_unlock(phs->forks + phs->n_philos - 1); // Unlock left fork for the first philosopher
// 	}
// 	else
// 	{
// 		*(phs->is_muted + thread_vars->pos - 1) = fork_status;
// 		if (status == LOCKED)
// 			pthread_mutex_lock(phs->forks + thread_vars->pos - 1); // Lock left fork for other philosophers
// 		else
// 			pthread_mutex_unlock(phs->forks + thread_vars->pos - 1); // Unlock left fork for other philosophers
// 	}

// 	// Update the right fork's mutex
// 	if (status == LOCKED)
// 		pthread_mutex_lock(phs->forks + thread_vars->pos); // Lock right fork
// 	else
// 		pthread_mutex_unlock(phs->forks + thread_vars->pos); // Unlock right fork
// }
