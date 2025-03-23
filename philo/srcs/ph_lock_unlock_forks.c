/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lock_unlock_forks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:07:24 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/23 13:08:13 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	lock_fork(t_inputs *phs, t_tv *tv, int fork_pos)
{
	ph_print_time(phs, tv, "has taken a fork");
	pthread_mutex_lock(phs->forks + fork_pos);
	pthread_mutex_lock(phs->forks_mute + fork_pos);
	phs->is_muted[fork_pos] = 1;
	pthread_mutex_unlock(phs->forks_mute + fork_pos);
}

int	ph_lock_forks(t_inputs *phs, t_tv *tv)
{
	if (tv->left_fork_pos < tv->right_fork_pos)
	{
		lock_fork(phs, tv, tv->left_fork_pos);
		lock_fork(phs, tv, tv->right_fork_pos);
	}
	else
	{
		lock_fork(phs, tv, tv->right_fork_pos);
		lock_fork(phs, tv, tv->left_fork_pos);
	}
	return (1);
}

void	unlock_fork(t_inputs *phs, int fork_pos)
{
	pthread_mutex_lock(phs->forks_mute + fork_pos);
	if (phs->is_muted[fork_pos])
	{
		phs->is_muted[fork_pos] = 0;
		pthread_mutex_unlock(phs->forks + fork_pos);
	}
	pthread_mutex_unlock(phs->forks_mute + fork_pos);
}

int	ph_unlock_forks(t_inputs *phs, t_tv *tv)
{
	if (tv->left_fork_pos < tv->right_fork_pos)
	{
		unlock_fork(phs, tv->right_fork_pos);
		unlock_fork(phs, tv->left_fork_pos);
	}
	else
	{
		unlock_fork(phs, tv->left_fork_pos);
		unlock_fork(phs, tv->right_fork_pos);
	}
	return (1);
}
