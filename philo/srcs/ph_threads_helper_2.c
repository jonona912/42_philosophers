/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_helper_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:09:03 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/23 13:08:11 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	lock_forks_mutex(t_inputs *phs, t_tv *tv)
{
	if (tv->left_fork_pos > tv->right_fork_pos)
	{
		pthread_mutex_lock(phs->forks_mute + tv->right_fork_pos);
		pthread_mutex_lock(phs->forks_mute + tv->left_fork_pos);
	}
	else
	{
		pthread_mutex_lock(phs->forks_mute + tv->left_fork_pos);
		pthread_mutex_lock(phs->forks_mute + tv->right_fork_pos);
	}
}

void	unlock_forks_mutex(t_inputs *phs, t_tv *tv)
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
