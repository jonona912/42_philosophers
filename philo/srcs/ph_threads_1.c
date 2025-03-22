/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:35:14 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:56:26 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	more_than_one_philo_cycles(t_inputs *phs, t_tv *tv)
{
	while (tv->i < phs->num_eat)
	{
		if (philo_eat_loop(phs, tv, phs->tte) == -1)
			return ;
		// printf("philo left eat loop %d\n", tv->pos + 1);
		ph_unlock_forks(phs, tv);
		// ph_set_queue(phs, tv->pos);
		ph_set_queue_2(phs, tv);
		if (philo_sleep_loop(phs, tv, phs->tts) == -1)
			return ;
		if (philo_thinking(phs, tv) == -1)
			return ;
		ph_lock_forks(phs, tv);
		ph_remove_first_queue(phs, tv);
		if (phs->is_num_eat)
			tv->i++;
	}
	ph_unlock_forks(phs, tv);
}

void	*more_than_one_philo(void *arg)
{
	t_inputs		*phs;
	t_tv	tv;

	phs = (t_inputs *)arg;
	initialize_tv(phs, &tv);
	set_philosopher_position(phs, &tv);
	set_philosopher_forks(phs, &tv);
	gettimeofday(&tv.time_ate, NULL);
	gettimeofday(&tv.prev_time, NULL);
	if ((tv.pos + 1) % 2 == 1)
	{
		ph_set_queue_2(phs, &tv);
		if (philo_sleep_loop(phs, &tv, phs->tts) == -1)  // STOPPED HERE
			return (NULL);
		if (philo_thinking(phs, &tv) == -1)
			return (NULL);
		ph_lock_forks(phs, &tv);
		ph_remove_first_queue(phs, &tv);
	}
	else
		ph_lock_forks(phs, &tv);
	more_than_one_philo_cycles(phs, &tv);
	return (NULL);
}

int create_and_join_threads(pthread_t *philos, t_inputs *crit)
{
	int	i;

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
			if (pthread_create((philos + i++), NULL, more_than_one_philo, crit) != 0)
				return (-1);
		}
		i = 0;
		while (i < crit->n_philos)
		{
			if (pthread_join(*(philos + i++), NULL) != 0)
				return (-1);
		}
	}
	return (0);
}










// void wait_for_forks(t_inputs *phs, t_tv *tv)
// {
// 	while (1)
// 	{
// 		// Check if the philosopher is at position 0 and is next in the queue
// 		if (tv->pos == 0 && phs->n_philos > 1 && tv->pos == phs->queue[tv->pos][0])
// 		{
// 			// Check if the right and left forks are available
// 			if (!*(phs->is_muted + tv->pos) && !*(phs->is_muted + phs->n_philos - 1))
// 			{
// 				ph_remove_first_queue(phs, tv); // Remove from the queue
// 				break; // Exit the loop
// 			}
// 		}
// 		// Check if the philosopher is next in the queue
// 		else if (tv->pos == phs->queue[tv->pos][0])
// 		{
// 			// Check if the right and left forks are available
// 			if (!*(phs->is_muted + tv->pos) && !*(phs->is_muted + tv->pos - 1))
// 			{
// 				ph_remove_first_queue(phs, tv); // Remove from the queue
// 				break; // Exit the loop
// 			}
// 		}
// 	}
// }

// void lock_forks(t_inputs *phs, t_tv *tv, t_lock_status status)
// {
// 	int fork_status = (status == LOCKED) ? 1 : 0; // Set fork_status based on the enum

// 	// Update the right fork
// 	*(phs->is_muted + tv->pos) = fork_status;

// 	// Update the left fork based on the philosopher's position
// 	if (tv->pos == 0)
// 	{
// 		*(phs->is_muted + tv->pos) = fork_status;
// 		if (status == LOCKED)
// 			pthread_mutex_lock(phs->forks + phs->n_philos - 1); // Lock left fork for the first philosopher
// 		else
// 			pthread_mutex_unlock(phs->forks + phs->n_philos - 1); // Unlock left fork for the first philosopher
// 	}
// 	else
// 	{
// 		*(phs->is_muted + tv->pos - 1) = fork_status;
// 		if (status == LOCKED)
// 			pthread_mutex_lock(phs->forks + tv->pos - 1); // Lock left fork for other philosophers
// 		else
// 			pthread_mutex_unlock(phs->forks + tv->pos - 1); // Unlock left fork for other philosophers
// 	}

// 	// Update the right fork's mutex
// 	if (status == LOCKED)
// 		pthread_mutex_lock(phs->forks + tv->pos); // Lock right fork
// 	else
// 		pthread_mutex_unlock(phs->forks + tv->pos); // Unlock right fork
// }
