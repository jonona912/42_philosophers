/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:46:48 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/23 12:30:49 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	philo_eat_loop(t_inputs *phs, t_tv *tv, long utime)
{
	gettimeofday(&tv->time_ate, NULL);
	if (utime < 0 || has_philosopher_died(phs))
		return (-1);
	ph_print_time(phs, tv, "is eating");
	gettimeofday(&tv->prev_time, NULL);
	while (return_time_microsec(tv->time_ate, tv->prev_time) + 50 < utime)
	{
		if (has_philosopher_died(phs))
		{
			ph_unlock_forks(phs, tv);
			return (-1);
		}
		usleep(10);
		gettimeofday(&tv->prev_time, NULL);
	}
	return (0);
}

int	philo_sleep_loop(t_inputs *phs, t_tv *tv, long utime)
{
	if (utime < 0 || check_philo_life_status(phs, tv) == -1)
		return (-1);
	gettimeofday(&tv->current_time, NULL);
	ph_print_time(phs, tv, "is sleeping");
	while (return_time_microsec(tv->prev_time, tv->current_time) + 50 < utime)
	{
		if (check_philo_life_status(phs, tv) == -1)
			return (-1);
		usleep(10);
		gettimeofday(&tv->current_time, NULL);
	}
	return (0);
}

int	philo_thinking_helper(t_inputs *phs, t_tv *tv, int *l_fp, int *r_fp)
{
	lock_forks_mutex(phs, tv);
	pthread_mutex_lock(&phs->queue_mutex);
	if (*l_fp == 0 && tv->pos + 1 == phs->queue[tv->left_fork_pos][0]
		&& !phs->is_muted[tv->left_fork_pos])
		*l_fp = 1;
	if (*r_fp == 0 && tv->pos + 1 == phs->queue[tv->right_fork_pos][0]
		&& !phs->is_muted[tv->right_fork_pos])
		*r_fp = 1;
	pthread_mutex_unlock(&phs->queue_mutex);
	unlock_forks_mutex(phs, tv);
	return (1);
}

int	philo_thinking(t_inputs *phs, t_tv *tv)
{
	int	l_fork_picked;
	int	r_fork_picked;

	l_fork_picked = 0;
	r_fork_picked = 0;
	if (check_philo_life_status(phs, tv) == -1)
		return (-1);
	ph_print_time(phs, tv, "is thinking");
	while (1)
	{
		philo_thinking_helper(phs, tv, &l_fork_picked, &r_fork_picked);
		if (l_fork_picked && r_fork_picked)
			break ;
		if (check_philo_life_status(phs, tv) == -1)
			return (-1);
		usleep(50);
	}
	gettimeofday(&tv->prev_time, NULL);
	return (0);
}
