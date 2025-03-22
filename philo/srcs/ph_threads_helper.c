/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:46:48 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:55:26 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// int	has_philosopher_died(t_inputs *phs)
// {
// 	int	is_dead;

// 	is_dead = 0;
// 	pthread_mutex_lock(&phs->death);
// 	is_dead = phs->is_dead;
// 	pthread_mutex_unlock(&phs->death);
// 	return (is_dead);
// }

// int	is_philo_dead_of_hunger(t_inputs *phs, t_tv *tv)
// {
// 	gettimeofday(&tv->current_time, NULL);
// 	if ((return_time_microsec(tv->time_ate, tv->current_time)) > tv->ttd_thread)
// 	{
// 		pthread_mutex_lock(&phs->death);
// 		phs->is_dead = 1;
// 		pthread_mutex_unlock(&phs->death);
// 		ph_print_time(phs, tv, "died");
// 		return (1);
// 	}
// 	return (0);
// }

// int	check_philo_life_status(t_inputs *phs, t_tv *tv)
// {
// 	if (has_philosopher_died(phs))
// 		return (-1);
// 	if (is_philo_dead_of_hunger(phs, tv))
// 		return (-1);
// 	return (0);
// }

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
		usleep(10);
		gettimeofday(&tv->current_time, NULL);
		if (check_philo_life_status(phs, tv) == -1)
			return (-1);
	}
	return (0);
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
		ph_forks_mutex_change(phs, tv, LOCK);
		pthread_mutex_lock(&phs->queue_mutex);
		if (l_fork_picked == 0 && tv->pos + 1 == phs->queue[tv->left_fork_pos][0] && !phs->is_muted[tv->left_fork_pos])
			l_fork_picked = 1;
		if (r_fork_picked == 0 && tv->pos + 1 == phs->queue[tv->right_fork_pos][0] && !phs->is_muted[tv->right_fork_pos])
			r_fork_picked = 1;
		pthread_mutex_unlock(&phs->queue_mutex);
		ph_forks_mutex_change(phs, tv, UNLOCK);
		if (l_fork_picked && r_fork_picked)
			break ;
		if (check_philo_life_status(phs, tv) == -1)
			return (-1);
		usleep(50);
		gettimeofday(&tv->prev_time, NULL);
	}
	return (0);
}
