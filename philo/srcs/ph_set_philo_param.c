/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_set_philo_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:41:48 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:55:26 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_philosopher_position(t_inputs *phs, t_tv *tv)
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
	tv->pos = i;
}

void	set_philosopher_forks(t_inputs *phs, t_tv *tv)
{
	if (tv->pos == 0)
	{
		tv->left_fork_pos = phs->n_philos - 1;
		tv->right_fork_pos = tv->pos;
	}
	else
	{
		tv->left_fork_pos = tv->pos - 1;
		tv->right_fork_pos = tv->pos;
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

void	initialize_tv(t_inputs *phs, t_tv *tv)
{
	memset(&tv->time_thought, 0, sizeof(struct timeval));
	memset(&tv->time_ate, 0, sizeof(struct timeval));
	memset(&tv->prev_time, 0, sizeof(struct timeval));
	memset(&tv->current_time, 0, sizeof(struct timeval));
	tv->left_fork_pos = 0;
	tv->right_fork_pos = 0;
	tv->pos = 0;
	tv->i = 0;
	tv->flag = 0;
	tv->ttd_thread = phs->ttd;
	tv->tte_thread = phs->tte;
	tv->tts_thread = phs->tts;
	tv->num_eat_thread = phs->num_eat;
	tv->is_num_eat_thread = phs->is_num_eat;
	tv->sleep_interval = 9000;
}
