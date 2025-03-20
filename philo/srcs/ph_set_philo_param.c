/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_set_philo_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:41:48 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/20 23:39:07 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_philosopher_position(t_inputs *phs, t_thread_vars *thread_vars)
{
	int i = 0;

	pthread_mutex_lock(&phs->mute_position);
	while (i < phs->n_philos)
	{
		if (!*(phs->ph_pos + i))
		{
			*(phs->ph_pos + i) = 1;
			break;
		}
		i++;
	}
	pthread_mutex_unlock(&phs->mute_position);
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

int	ph_initialize_mutexes(t_inputs *phs)
{
	int i = 0;

	while (i < phs->n_philos)
	{
		if (pthread_mutex_init(phs->forks + i, NULL) != 0)
			return (-1);
		if (pthread_mutex_init(phs->forks_mute + i, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&phs->print, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&phs->death, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&phs->mute_position, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&phs->queue_mutex, NULL) != 0)
		return (-1);
	return (0);
}

void	initialize_thread_vars(t_inputs *phs, t_thread_vars *thread_vars)
{
	memset(&thread_vars->time_thought, 0, sizeof(struct timeval));
	memset(&thread_vars->time_ate, 0, sizeof(struct timeval));
	memset(&thread_vars->prev_time, 0, sizeof(struct timeval));
	memset(&thread_vars->current_time, 0, sizeof(struct timeval));
	thread_vars->left_fork_pos = 0;
	thread_vars->right_fork_pos = 0;
	thread_vars->pos = 0;
	thread_vars->i = 0;
	thread_vars->flag = 0;
	thread_vars->ttd_thread = phs->ttd;
	thread_vars->tte_thread = phs->tte;
	thread_vars->tts_thread = phs->tts;
	thread_vars->num_eat_thread = phs->num_eat;
	thread_vars->is_num_eat_thread = phs->is_num_eat;
	thread_vars->sleep_interval = 9000; // 9miliseconds
}


