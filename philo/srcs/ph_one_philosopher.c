/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_one_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:07:21 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/20 23:32:55 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	one_philo_thinking(t_inputs *phs, t_thread_vars *thread_vars, long time_to_think)
{
	struct timeval	prev_time;

	ph_print_time(phs, thread_vars, "is thinking");
	time_to_think *= 1000;
	while (time_to_think > thread_vars->sleep_interval)
	{
		gettimeofday(&prev_time, NULL);
		usleep(thread_vars->sleep_interval - 100);
		gettimeofday(&thread_vars->current_time, NULL);
		time_to_think -= return_time_microsec(prev_time, thread_vars->current_time);
	}
	usleep(time_to_think);
}

void	*philosopher_activity(void *arg)
{
	t_thread_vars	thread_vars;
	int				i;
	long			time_to_think;
	t_inputs 		*phs;

	phs	= (t_inputs *)arg;
	initialize_thread_vars(phs, &thread_vars);
	set_philosopher_position(phs, &thread_vars);
	i = 0;
	while (i < phs->num_eat)
	{
		ph_print_time(phs, &thread_vars, "has taken a fork");
		philo_eat_loop(phs, &thread_vars, phs->tte);
		if (philo_sleep_loop(phs, &thread_vars, phs->tts) == -1)
			return (NULL);
		gettimeofday(&thread_vars.current_time, NULL);
		time_to_think = return_time_microsec(thread_vars.time_ate, thread_vars.current_time) / 1000;
		if (time_to_think > phs->ttd)
			one_philo_thinking(phs, &thread_vars, time_to_think);
		if (phs->is_num_eat)
			i++;
	}
	return (NULL);
}
