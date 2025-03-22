/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:39:39 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:55:26 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


int check_forks_locked(t_inputs *phs, t_tv *tv)
{
	if (pthread_mutex_trylock(phs->forks + tv->left_fork_pos) != 0)
	{
		printf("\033[0;31mLeft fork %d is locked\033[0m\n", tv->left_fork_pos);
	}
	else
	{
		pthread_mutex_unlock(phs->forks + tv->left_fork_pos);
	}

	if (pthread_mutex_trylock(phs->forks + tv->right_fork_pos) != 0)
	{
		printf("\033[0;31mRight fork %d is locked\033[0m\n", tv->right_fork_pos);
	}
	else
	{
		pthread_mutex_unlock(phs->forks + tv->right_fork_pos);
	}
	if (pthread_mutex_trylock(&phs->print) != 0)
	{
		printf("\033[0;31mPrint mutex is locked by philo %d\033[0m\n", tv->pos + 1);
	}
	else
	{
		pthread_mutex_unlock(&phs->print);
	}

	if (pthread_mutex_trylock(&phs->death) != 0)
	{
		printf("\033[0;31mDeath mutex is locked\033[0m\n");
	}
	else
	{
		pthread_mutex_unlock(&phs->death);
	}

	if (pthread_mutex_trylock(&phs->mute_position) != 0)
	{
		printf("\033[0;31mMake change mutex is locked\033[0m\n");
	}
	else
	{
		pthread_mutex_unlock(&phs->mute_position);
	}

	if (pthread_mutex_trylock(&phs->queue_mutex) != 0)
	{
		printf("\033[0;31mQueue mutex is locked\033[0m\n");
	}
	else
	{
		pthread_mutex_unlock(&phs->queue_mutex);
	}
	return (1);
}
