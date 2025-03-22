/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_helper_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:09:03 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:55:26 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int ph_forks_mutex_change(t_inputs *phs, t_tv *tv, t_lock_status status)
{
	if (status == LOCK)
	{
		if (tv->left_fork_pos > tv->right_fork_pos)
		{
			pthread_mutex_lock(phs->forks_mute + tv->right_fork_pos);  // this is in 3 places, make it a seperate function
			pthread_mutex_lock(phs->forks_mute + tv->left_fork_pos); // if function fails?
		}
		else
		{
			pthread_mutex_lock(phs->forks_mute + tv->left_fork_pos);
			pthread_mutex_lock(phs->forks_mute + tv->right_fork_pos);
		}
	}
	else if (status == UNLOCK)
	{
		if (tv->left_fork_pos > tv->right_fork_pos)
		{
			pthread_mutex_unlock(phs->forks_mute + tv->left_fork_pos);
			pthread_mutex_unlock(phs->forks_mute + tv->right_fork_pos);
		}
		else
		{
			pthread_mutex_unlock(phs->forks_mute + tv->right_fork_pos);
			pthread_mutex_unlock(phs->forks_mute + tv->left_fork_pos);
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


int ph_lock_forks(t_inputs *phs, t_tv *tv)
{
	// ph_forks_mutex_change(phs, tv, LOCK);
	// printf("philo %d locking forks %d %d\n", tv->pos + 1, tv->left_fork_pos, tv->right_fork_pos);
	// printf("philo %d is_muted %d %d\n", tv->pos + 1, phs->is_muted[tv->left_fork_pos], phs->is_muted[tv->right_fork_pos]);
	if (tv->left_fork_pos < tv->right_fork_pos)
	{
		ph_print_time(phs, tv, "has taken a fork");
		pthread_mutex_lock(phs->forks + tv->left_fork_pos); // lock for changing the forks
		pthread_mutex_lock(phs->forks_mute + tv->left_fork_pos);
		phs->is_muted[tv->left_fork_pos] = 1;
		pthread_mutex_unlock(phs->forks_mute + tv->left_fork_pos);
		// set_is_muted(phs, tv->left_fork_pos, 1);
		ph_print_time(phs, tv, "has taken a fork");
		pthread_mutex_lock(phs->forks + tv->right_fork_pos);
		pthread_mutex_lock(phs->forks_mute + tv->right_fork_pos);
		phs->is_muted[tv->right_fork_pos] = 1;
		pthread_mutex_unlock(phs->forks_mute + tv->right_fork_pos);
		// set_is_muted(phs, tv->right_fork_pos, 1);
	}
	else
	{
		ph_print_time(phs, tv, "has taken a fork");
		pthread_mutex_lock(phs->forks + tv->right_fork_pos);
		pthread_mutex_lock(phs->forks_mute + tv->right_fork_pos);
		phs->is_muted[tv->right_fork_pos] = 1;
		pthread_mutex_unlock(phs->forks_mute + tv->right_fork_pos);
		ph_print_time(phs, tv, "has taken a fork");
		pthread_mutex_lock(phs->forks + tv->left_fork_pos);
		pthread_mutex_lock(phs->forks_mute + tv->left_fork_pos);
		phs->is_muted[tv->left_fork_pos] = 1;
		pthread_mutex_unlock(phs->forks_mute + tv->left_fork_pos);
	}
	// ph_forks_mutex_change(phs, tv, UNLOCK);
	// printf("philo %d is_muted %d %d <=====================\n", tv->pos + 1, phs->is_muted[tv->left_fork_pos], phs->is_muted[tv->right_fork_pos]);
	return (1);
}

int ph_unlock_forks(t_inputs *phs, t_tv *tv)
{
	// ph_forks_mutex_change(phs, tv, LOCK);
	int i = 0;
	if (tv->left_fork_pos < tv->right_fork_pos)
	{
		pthread_mutex_lock(phs->forks_mute + tv->right_fork_pos);
		if (phs->is_muted[tv->right_fork_pos])
		{
			// set_is_muted(phs, tv->right_fork_pos, 0);
			phs->is_muted[tv->right_fork_pos] = 0;
			pthread_mutex_unlock(phs->forks + tv->right_fork_pos);
			i++;
		}
		pthread_mutex_unlock(phs->forks_mute + tv->right_fork_pos);
		pthread_mutex_lock(phs->forks_mute + tv->left_fork_pos);
		if (phs->is_muted[tv->left_fork_pos])
		{
			phs->is_muted[tv->left_fork_pos] = 0;
			// set_is_muted(phs, tv->left_fork_pos, 0);
			pthread_mutex_unlock(phs->forks + tv->left_fork_pos);
			i++;
		}
		pthread_mutex_unlock(phs->forks_mute + tv->left_fork_pos);
	}
	else
	{
		pthread_mutex_lock(phs->forks_mute + tv->left_fork_pos);
		if (phs->is_muted[tv->left_fork_pos])
		{
			// set_is_muted(phs, tv->left_fork_pos, 0);
			phs->is_muted[tv->left_fork_pos] = 0;
			pthread_mutex_unlock(phs->forks + tv->left_fork_pos);
			i++;
		}
		pthread_mutex_unlock(phs->forks_mute + tv->left_fork_pos);
		pthread_mutex_lock(phs->forks_mute + tv->right_fork_pos);
		if (phs->is_muted[tv->right_fork_pos])
		{
			// set_is_muted(phs, tv->right_fork_pos, 0);
			phs->is_muted[tv->right_fork_pos] = 0;
			pthread_mutex_unlock(phs->forks + tv->right_fork_pos);
			i++;
		}
		pthread_mutex_unlock(phs->forks_mute + tv->right_fork_pos);
	}
	// if (i == 2)
	// {
	// 	pthread_mutex_lock(&phs->print);
	// 	printf("\033[0;32mPhilosopher %d has released the forks LEFT %d RIGHT %d\033[0m\n", 
	// 		tv->pos + 1, tv->left_fork_pos + 1, tv->right_fork_pos + 1);
	// 	printf("\033[0;32m mute status 1st: %d 2nd %d 3rd %d\033[0m\n", phs->is_muted[0], phs->is_muted[1], phs->is_muted[2]);
	// 	pthread_mutex_unlock(&phs->print);
	// }
	// ph_forks_mutex_change(phs, tv, UNLOCK);
	return (1);	
}
