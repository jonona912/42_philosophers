/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:35:14 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/23 13:30:33 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_thread_cycles(t_inputs *phs, t_tv *tv)
{
	while (tv->i < phs->num_eat)
	{
		if (philo_eat_loop(phs, tv, phs->tte) == -1)
			return ;
		ph_unlock_forks(phs, tv);
		ph_set_queue_2(phs, tv);
		if (philo_sleep_loop(phs, tv, phs->tts) == -1)
			return ;
		if (philo_thinking(phs, tv) == -1)
			return ;
		ph_lock_forks(phs, tv);
		ph_remove_first_queue(phs, tv);
		if (phs->is_num_eat)
			tv->i++;
	}
	ph_unlock_forks(phs, tv);
}

void	*philo_thread(void *arg)
{
	t_inputs		*phs;
	t_tv			tv;

	phs = (t_inputs *)arg;
	initialize_tv(phs, &tv);
	set_philosopher_position(phs, &tv);
	set_philosopher_forks(phs, &tv);
	gettimeofday(&tv.time_ate, NULL);
	gettimeofday(&tv.prev_time, NULL);
	if ((tv.pos + 1) % 2 == 1)
	{
		ph_set_queue_2(phs, &tv);
		if (philo_sleep_loop(phs, &tv, phs->tts) == -1)
			return (NULL);
		if (philo_thinking(phs, &tv) == -1)
			return (NULL);
		ph_lock_forks(phs, &tv);
		ph_remove_first_queue(phs, &tv);
	}
	else
		ph_lock_forks(phs, &tv);
	philo_thread_cycles(phs, &tv);
	return (NULL);
}

void	*one_philosopher(void *arg)
{
	t_tv		tv;
	t_inputs	*phs;

	phs = (t_inputs *) arg;
	initialize_tv(phs, &tv);
	set_philosopher_position(phs, &tv);
	ph_print_time(phs, &tv, "has taken a fork");
	usleep(phs->ttd);
	ph_print_time(phs, &tv, "died");
	return (NULL);
}

int	create_and_join_threads(pthread_t *philos, t_inputs *crit)
{
	int	i;

	if (crit->n_philos == 1)
	{
		if (pthread_create(philos, NULL, one_philosopher, crit) != 0)
			return (-1);
		if (pthread_join(*philos, NULL) != 0)
			return (-1);
	}
	else
	{
		i = 0;
		while (i < crit->n_philos)
		{
			if (pthread_create((philos + i++), NULL, philo_thread, crit) != 0)
				return (-1);
		}
		i = 0;
		while (i < crit->n_philos)
		{
			if (pthread_join(*(philos + i++), NULL) != 0)
				return (-1);
		}
	}
	return (0);
}
