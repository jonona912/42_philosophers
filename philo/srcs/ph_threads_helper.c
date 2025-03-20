/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:46:48 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/20 23:53:00 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* seems like everything is locked and unlocked in eat loop: DEATH CHECK
AND FORK_UNLOCK in case of failure*/

int	has_philosopher_died(t_inputs *phs)
{
	int	is_dead;

	is_dead = 0;
	pthread_mutex_lock(&phs->death);
	is_dead = phs->is_dead;
	pthread_mutex_unlock(&phs->death);
	return (is_dead);
}

int	is_philo_dead_of_hunger(t_inputs *phs, t_thread_vars *thread_vars)
{
	gettimeofday(&thread_vars->current_time, NULL);
	if ((return_time_microsec(thread_vars->time_ate, thread_vars->current_time)) > thread_vars->ttd_thread) // fix the return time
	{
		pthread_mutex_lock(&phs->death);
		phs->is_dead = 1;
		pthread_mutex_unlock(&phs->death);
		ph_print_time(phs, thread_vars, "died");
		return (1);
	}
	return (0);
}

int	check_philo_life_status(t_inputs *phs, t_thread_vars *thread_vars)
{
	if (has_philosopher_died(phs))
		return (-1);
	if (is_philo_dead_of_hunger(phs, thread_vars))
		return (-1);
	return (0);
}

int	philo_eat_loop(t_inputs *phs, t_thread_vars *thread_vars, long utime)
{
	// struct timeval	prev_time; // remove this
	long			time_accum;

	time_accum = 0;
	if (utime < 0 || check_philo_life_status(phs, thread_vars) == -1)
		return (-1);
	ph_print_time(phs, thread_vars, "is eating");
	// gettimeofday(&prev_time, NULL);
	while (utime > thread_vars->sleep_interval)
	{
		if (has_philosopher_died(phs))
		{
			ph_unlock_forks(phs, thread_vars);
			return (-1);
		}
		usleep(thread_vars->sleep_interval - 100);
		gettimeofday(&thread_vars->current_time, NULL);
		utime -= return_time_microsec(thread_vars->prev_time, thread_vars->current_time);
		thread_vars->prev_time = thread_vars->current_time;
	}
	usleep(utime);
	gettimeofday(&thread_vars->time_ate, NULL);
	return (0);
}

int	philo_sleep_loop(t_inputs *phs, t_thread_vars *thread_vars, long utime)
{
	// struct timeval	prev_time;

	if (utime < 0 || check_philo_life_status(phs, thread_vars) == -1) // comment for time
		return (-1);
	ph_print_time(phs, thread_vars, "is sleeping");
	// thread_vars->prev_time = thread_vars->time_ate;
	while (utime > thread_vars->sleep_interval)
	{
		// gettimeofday(&prev_time, NULL);
		usleep(thread_vars->sleep_interval);
		gettimeofday(&thread_vars->current_time, NULL);
		utime -= return_time_microsec(thread_vars->prev_time, thread_vars->current_time);
		if (check_philo_life_status(phs, thread_vars) == -1)
			return (-1);
		thread_vars->prev_time = thread_vars->current_time;
	}
	usleep(utime);
	thread_vars->prev_time = thread_vars->current_time;
	return (0);
}

// send philosopher to think
// int	philo_thinking(t_inputs *phs, t_thread_vars *thread_vars)
// {
// 	int	num_forks_picked;
// 	num_forks_picked = 0;
// 	ph_print_time(phs, thread_vars, "is thinking");
// 	while (1)
// 	{
// 		gettimeofday(&thread_vars->current_time, NULL);
// 		if (phs->is_dead)
// 		{
// 			ph_print_time(phs, thread_vars, "died");
// 			return (-1);
// 		}
// 		if (is_philo_dead_of_hunger(phs, thread_vars))
// 			return (-1);
// 		// pthread_mutex_lock(phs->forks_mute + thread_vars->left_fork_pos);
// 		// pthread_mutex_lock(phs->forks_mute + thread_vars->right_fork_pos);
// 		if (thread_vars->pos == phs->queue[thread_vars->pos][0] && !phs->is_muted[thread_vars->left_fork_pos])
// 			num_forks_picked += ph_lock_forks(phs, thread_vars, LEFT_FORK);  //pick_a_fork(phs, thread_vars, thread_vars->left_fork_pos);
// 		if (thread_vars->pos == phs->queue[thread_vars->pos][0] && !phs->is_muted[thread_vars->right_fork_pos])
// 			num_forks_picked += ph_lock_forks(phs, thread_vars, RIGHT_FORK); // pick_a_fork(phs, thread_vars, thread_vars->right_fork_pos);
// 		// pthread_mutex_unlock(phs->forks_mute + thread_vars->right_fork_pos);
// 		// pthread_mutex_unlock(phs->forks_mute + thread_vars->left_fork_pos);
// 		if (num_forks_picked == 2)
// 		{
// 			ph_remove_first_queue(phs, thread_vars);
// 			break ;
// 		}
// 		usleep(100);
// 	}
// 	return (0);
// }

int	philo_thinking(t_inputs *phs, t_thread_vars *thread_vars)
{
	int	l_fork_picked;
	int	r_fork_picked;

	l_fork_picked = 0;
	r_fork_picked = 0;
	if (check_philo_life_status(phs, thread_vars) == -1)
		return (-1);
	ph_print_time(phs, thread_vars, "is thinking");
	while (1)
	{
		if (check_philo_life_status(phs, thread_vars) == -1)
			return (-1);
		gettimeofday(&thread_vars->current_time, NULL);
		if (l_fork_picked && r_fork_picked)
			break ;
		ph_forks_mutex_change(phs, thread_vars, LOCK);
		pthread_mutex_lock(&phs->queue_mutex);
		if (thread_vars->pos == phs->queue[thread_vars->pos][0] && !phs->is_muted[thread_vars->left_fork_pos])
			l_fork_picked = 1;
		if (thread_vars->pos == phs->queue[thread_vars->pos][0] && !phs->is_muted[thread_vars->right_fork_pos])
			r_fork_picked = 1;
		pthread_mutex_unlock(&phs->queue_mutex);
		ph_forks_mutex_change(phs, thread_vars, UNLOCK);
		usleep(100);
	}
	gettimeofday(&thread_vars->prev_time, NULL);
	return (0);
}
