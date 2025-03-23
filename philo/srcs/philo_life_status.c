/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 23:52:10 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:56:51 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	has_philosopher_died(t_inputs *phs)
{
	int	is_dead;

	is_dead = 0;
	pthread_mutex_lock(&phs->death);
	is_dead = phs->is_dead;
	pthread_mutex_unlock(&phs->death);
	return (is_dead);
}

int	is_philo_dead_of_hunger(t_inputs *phs, t_tv *tv)
{
	gettimeofday(&tv->current_time, NULL);
	if ((return_time_microsec(tv->time_ate, tv->current_time)) > tv->ttd_thread)
	{
		pthread_mutex_lock(&phs->death);
		phs->is_dead = 1;
		pthread_mutex_unlock(&phs->death);
		ph_print_time(phs, tv, "died");
		return (1);
	}
	return (0);
}

int	check_philo_life_status(t_inputs *phs, t_tv *tv)
{
	if (has_philosopher_died(phs))
		return (-1);
	if (is_philo_dead_of_hunger(phs, tv))
		return (-1);
	return (0);
}
