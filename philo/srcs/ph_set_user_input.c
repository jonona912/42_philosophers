/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_set_user_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:03:13 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/23 13:21:01 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ph_set_user_inputs_helper(t_inputs *crit)
{
	int	i;

	i = 0;
	crit->forks
		= (pthread_mutex_t *)malloc(crit->n_philos * sizeof(pthread_mutex_t));
	crit->forks_mute
		= (pthread_mutex_t *)malloc(crit->n_philos * sizeof(pthread_mutex_t));
	if (!crit->forks)
		return (-1);
	crit->is_muted = (int *)malloc(crit->n_philos * sizeof(int));
	crit->ph_pos = NULL;
	crit->queue = NULL;
	if (!crit->is_muted)
		return (free_t_inputs(crit), -1);
	ph_set_int_zero(&crit->is_muted, crit->n_philos);
	crit->ph_pos = (int *)malloc(crit->n_philos * sizeof(int));
	if (!crit->ph_pos)
		return (free_t_inputs(crit), -1);
	ph_set_int_zero(&(crit->ph_pos), crit->n_philos);
	if (ph_allocate_queue(crit) == -1)
		return (-1);
	return (1);
}

int	ph_set_user_inputs(t_inputs *crit, char **argv)
{
	int	i;

	i = 0;
	crit->n_philos = ph_atoi(*(argv + ++i));
	if (crit->n_philos > 200)
		return (printf("Number of philosophers must be less than 200\n"), -1);
	crit->ttd = ph_atoi(*(argv + ++i)) * 1000;
	crit->tte = ph_atoi(*(argv + ++i)) * 1000;
	crit->tts = ph_atoi(*(argv + ++i)) * 1000;
	crit->is_dead = 0;
	crit->total_queue = 2;
	if (*(argv + ++i))
	{
		crit->num_eat = ph_atoi(*(argv + i));
		crit->is_num_eat = 1;
	}
	else
	{
		crit->num_eat = 1;
		crit->is_num_eat = 0;
	}
	return (ph_set_user_inputs_helper(crit));
}
