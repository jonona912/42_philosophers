/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:39:39 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/08 17:51:34 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*
 * This function sets the position of a philosopher.
 * It initializes the index, finds an available philosopher position,
 * marks the position as taken, and sets the philosopher's position.
 */
void	set_philosopher_position(t_inputs *phs, t_thread_vars *thread_vars)
{
	int i = 0;

	while (i < phs->n_philos)
	{
		if (!*(phs->ph_pos + i))
		{
			*(phs->ph_pos + i) = 1;
			break;
		}
		i++;
	}
	thread_vars->pos = i;
}

void	set_philosopher_forks(t_inputs *phs, t_thread_vars *thread_vars)
{
	if (thread_vars->pos == 0)
	{
		thread_vars->left_fork_pos = phs->n_philos - 1;
		thread_vars->right_fork_pos = thread_vars->pos;
	}
	else
	{
		thread_vars->left_fork_pos = thread_vars->pos - 1;
		thread_vars->right_fork_pos = thread_vars->pos;
	}
}

// send philosopher to think
int	philo_thinking(t_inputs *phs, t_thread_vars *thread_vars)
{
	int	num_forks_picked;

	num_forks_picked = 0;
	// check every 10 ms if a philosopher died, if not then grab two forks
	while (1)
	{
		if (phs->is_dead)
		{
			printf("Philosopher died %d\n", thread_vars->pos);
			return (-1);
		}
		// check whether current philo is in queue and left and right fork are free
		if (thread_vars->pos == 0) // special case for the philosopher at position 0
		{
			if (thread_vars->pos == phs->queue[thread_vars->pos][0] && !phs->is_muted[phs->n_philos - 1]) // left fork and check if free
			{
				pthread_mutex_lock(phs->forks + phs->n_philos - 1); // lock left fork
				printf("Philosopher %d took a fork\n", thread_vars->pos);
				phs->is_muted[phs->n_philos - 1] = 1;
				// ph_remove_first_queue(phs, thread_vars);
				num_forks_picked++;
			}
		}
		else
		{
			if (thread_vars->pos == phs->queue[thread_vars->pos][0] && !phs->is_muted[thread_vars->pos - 1]) // left fork and check if free
			{
				pthread_mutex_lock(phs->forks + thread_vars->pos - 1); // lock left fork
				printf("Philosopher %d took a fork\n", thread_vars->pos);
				phs->is_muted[thread_vars->pos - 1] = 1;
				// ph_remove_first_queue(phs, thread_vars);
				num_forks_picked++;
			}
			if (thread_vars->pos == phs->queue[thread_vars->pos][0] && !phs->is_muted[thread_vars->pos]) // right fork and check if free
			{
				pthread_mutex_lock(phs->forks + thread_vars->pos); // lock right fork
				printf("Philosopher %d took a fork\n", thread_vars->pos);
				phs->is_muted[thread_vars->pos] = 1;
				// ph_remove_first_queue(phs, thread_vars);
				num_forks_picked++;
			}
			if (num_forks_picked == 2)
			{
				ph_remove_first_queue(phs, thread_vars);
				break ;
			}
			// don't forget usleept 10 ms and check if a philosopher died
		}
	}
	return (0);
}

// even num of philosophers
void	*even_num_philos(void *arg)
{
	// if the number of a philosopher is even then make it eat
	t_inputs *phs = (t_inputs *)arg;
	t_thread_vars	thread_vars;

	if (phs->n_philos % 2 == 1)
		return (NULL);
	// set philo position
	set_philosopher_position(phs, &thread_vars);
	// set left and right fork
	set_philosopher_forks(phs, &thread_vars);
	if (thread_vars.pos % 2 == 1)
	{
		ph_set_queue(phs, thread_vars.pos);
		philo_thinking(phs, &thread_vars);
	}
	while (thread_vars.i < phs->num_eat)
	{
		pthread_mutex_lock(phs->forks + thread_vars.pos);
		phs->is_muted[thread_vars.pos] = 1;
		printf("Philosopher %d is eating\n", thread_vars.pos);
		usleep(phs->tte);
		pthread_mutex_unlock(phs->forks + thread_vars.pos);
		phs->is_muted[thread_vars.pos] = 0;
		// set this philosopher in queue
		ph_set_queue(phs, thread_vars.pos);
		printf("Philosopher %d is sleeping\n", thread_vars.pos);
		usleep(phs->tts);
		philo_thinking(phs, &thread_vars);
		if (phs->is_num_eat)
			thread_vars.i++;
	}
	return (NULL);
	// while thinking the philosopher checks whether the fork is free


	// if odd send it to think
	// no need for queue - just wait for the fork to free
	// if the fork is free then lock it and eat
}



