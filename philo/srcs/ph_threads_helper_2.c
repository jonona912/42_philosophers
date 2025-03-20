/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_helper_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:09:03 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/20 21:35:07 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int ph_forks_mutex_change(t_inputs *phs, t_thread_vars *thread_vars, t_lock_status status)
{
	if (status == LOCK)
	{
		if (thread_vars->left_fork_pos > thread_vars->right_fork_pos)
		{
			pthread_mutex_lock(phs->forks_mute + thread_vars->right_fork_pos);  // this is in 3 places, make it a seperate function
			pthread_mutex_lock(phs->forks_mute + thread_vars->left_fork_pos); // if function fails?
		}
		else
		{
			pthread_mutex_lock(phs->forks_mute + thread_vars->left_fork_pos);
			pthread_mutex_lock(phs->forks_mute + thread_vars->right_fork_pos);
		}
	}
	else if (status == UNLOCK)
	{
		if (thread_vars->left_fork_pos > thread_vars->right_fork_pos)
		{
			pthread_mutex_unlock(phs->forks_mute + thread_vars->left_fork_pos);
			pthread_mutex_unlock(phs->forks_mute + thread_vars->right_fork_pos);
		}
		else
		{
			pthread_mutex_unlock(phs->forks_mute + thread_vars->right_fork_pos);
			pthread_mutex_unlock(phs->forks_mute + thread_vars->left_fork_pos);
		}
	}
	return (1);
}

void set_is_muted(t_inputs *phs, int index, int value)
{
	pthread_mutex_lock(phs->forks_mute + index);
	phs->is_muted[index] = value;
	pthread_mutex_unlock(phs->forks_mute + index);
}


int ph_lock_forks(t_inputs *phs, t_thread_vars *thread_vars)
{
	// ph_forks_mutex_change(phs, thread_vars, LOCK);
	if (thread_vars->left_fork_pos < thread_vars->right_fork_pos)
	{
		pthread_mutex_lock(phs->forks + thread_vars->left_fork_pos); // lock for changing the forks
		pthread_mutex_lock(phs->forks_mute + thread_vars->left_fork_pos);
		phs->is_muted[thread_vars->left_fork_pos] = 1;
		pthread_mutex_unlock(phs->forks_mute + thread_vars->left_fork_pos);
		// set_is_muted(phs, thread_vars->left_fork_pos, 1);
		ph_print_time(phs, thread_vars, "has taken a fork");
		pthread_mutex_lock(phs->forks + thread_vars->right_fork_pos);
		pthread_mutex_lock(phs->forks_mute + thread_vars->right_fork_pos);
		phs->is_muted[thread_vars->right_fork_pos] = 1;
		pthread_mutex_unlock(phs->forks_mute + thread_vars->right_fork_pos);
		// set_is_muted(phs, thread_vars->right_fork_pos, 1);
		ph_print_time(phs, thread_vars, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(phs->forks + thread_vars->right_fork_pos);
		pthread_mutex_lock(phs->forks_mute + thread_vars->right_fork_pos);
		phs->is_muted[thread_vars->right_fork_pos] = 1;
		pthread_mutex_unlock(phs->forks_mute + thread_vars->right_fork_pos);
		ph_print_time(phs, thread_vars, "has taken a fork");
		pthread_mutex_lock(phs->forks + thread_vars->left_fork_pos);
		pthread_mutex_lock(phs->forks_mute + thread_vars->left_fork_pos);
		phs->is_muted[thread_vars->left_fork_pos] = 1;
		pthread_mutex_unlock(phs->forks_mute + thread_vars->left_fork_pos);
		ph_print_time(phs, thread_vars, "has taken a fork");
	}
	// ph_forks_mutex_change(phs, thread_vars, UNLOCK);
	return (1);
}

int ph_unlock_forks(t_inputs *phs, t_thread_vars *thread_vars)
{
	// ph_forks_mutex_change(phs, thread_vars, LOCK);
	int i = 0;
	if (thread_vars->left_fork_pos < thread_vars->right_fork_pos)
	{
		pthread_mutex_lock(phs->forks_mute + thread_vars->right_fork_pos);
		if (phs->is_muted[thread_vars->right_fork_pos])
		{
			// set_is_muted(phs, thread_vars->right_fork_pos, 0);
			phs->is_muted[thread_vars->right_fork_pos] = 0;
			pthread_mutex_unlock(phs->forks + thread_vars->right_fork_pos);
			i++;
		}
		pthread_mutex_unlock(phs->forks_mute + thread_vars->right_fork_pos);
		pthread_mutex_lock(phs->forks_mute + thread_vars->left_fork_pos);
		if (phs->is_muted[thread_vars->left_fork_pos])
		{
			phs->is_muted[thread_vars->left_fork_pos] = 0;
			// set_is_muted(phs, thread_vars->left_fork_pos, 0);
			pthread_mutex_unlock(phs->forks + thread_vars->left_fork_pos);
			i++;
		}
		pthread_mutex_unlock(phs->forks_mute + thread_vars->left_fork_pos);
	}
	else
	{
		pthread_mutex_lock(phs->forks_mute + thread_vars->left_fork_pos);
		if (phs->is_muted[thread_vars->left_fork_pos])
		{
			// set_is_muted(phs, thread_vars->left_fork_pos, 0);
			phs->is_muted[thread_vars->left_fork_pos] = 0;
			pthread_mutex_unlock(phs->forks + thread_vars->left_fork_pos);
			i++;
		}
		pthread_mutex_unlock(phs->forks_mute + thread_vars->left_fork_pos);
		pthread_mutex_lock(phs->forks_mute + thread_vars->right_fork_pos);
		if (phs->is_muted[thread_vars->right_fork_pos])
		{
			// set_is_muted(phs, thread_vars->right_fork_pos, 0);
			phs->is_muted[thread_vars->right_fork_pos] = 0;
			pthread_mutex_unlock(phs->forks + thread_vars->right_fork_pos);
			i++;
		}
		pthread_mutex_unlock(phs->forks_mute + thread_vars->right_fork_pos);
	}
	// if (i == 2)
	// {
	// 	pthread_mutex_lock(&phs->print);
	// 	printf("\033[0;32mPhilosopher %d has released the forks\033[0m\n", thread_vars->pos + 1);
	// 	pthread_mutex_unlock(&phs->print);
	// }
	// ph_forks_mutex_change(phs, thread_vars, UNLOCK);
	return (1);	
}
