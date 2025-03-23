/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mem_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:27:44 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/23 13:05:01 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ph_free_double_arr(int ***arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if ((*arr)[i])
		{
			free((*arr)[i]);
			(*arr)[i] = NULL;
		}
		i++;
	}
	if (*arr)
	{
		free(*arr);
		*arr = NULL;
	}
}

void	ph_destroy_mutexes(t_inputs *phs)
{
	int	i;

	i = 0;
	while (i < phs->n_philos)
	{
		pthread_mutex_destroy(phs->forks + i);
		pthread_mutex_destroy(phs->forks_mute + i);
		i++;
	}
	pthread_mutex_destroy(&phs->print);
	pthread_mutex_destroy(&phs->death);
	pthread_mutex_destroy(&phs->mute_position);
	pthread_mutex_destroy(&phs->queue_mutex);
}

void	ph_free_memory(t_inputs *phs)
{
	ph_destroy_mutexes(phs);
	if (phs->forks)
	{
		free(phs->forks);
		phs->forks = NULL;
	}
	if (phs->is_muted)
	{
		free(phs->is_muted);
		phs->is_muted = NULL;
	}
	if (phs->ph_pos)
	{
		free(phs->ph_pos);
		phs->ph_pos = NULL;
	}
	if (phs->forks_mute)
	{
		free(phs->forks_mute);
		phs->forks_mute = NULL;
	}
	ph_free_double_arr(&phs->queue, phs->n_philos);
	return ;
}
