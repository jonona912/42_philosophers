/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_queues.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:09:14 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/21 20:01:22 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ph_set_queue(t_inputs *phs, int pos)
{
	int	i;

	i = 0;
	// pthread_mutex_lock(&phs->queue_mutex);
	while (i < phs->total_queue)
	{
		if (phs->queue[pos][i] == 0) // zero is a mistake because of zero position
		{
			*(*(phs->queue + pos) + i) = pos + 1;
			break;
		}
		i++;
	}
	printf("current fork pos %d first in queue %d second in queue %d\n", 
		pos + 1, phs->queue[pos][0], phs->queue[pos][1]);
	// pthread_mutex_unlock(&phs->queue_mutex);
	return (1);
}

int	ph_set_queue_2(t_inputs *phs, t_thread_vars *thread_vars)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&phs->queue_mutex);
	// set left queue in the queue
	ph_set_queue(phs, thread_vars->left_fork_pos);
	// set right queue in the queue
	ph_set_queue(phs, thread_vars->right_fork_pos);
	pthread_mutex_unlock(&phs->queue_mutex);
	return (1);
}

// void	ph_inplace_swap(int *a, int *b)
// {
// 	*a = *a ^ *b;
// 	*b = *a ^ *b;
// 	*a = *a ^ *b;
// }

void	ph_remove_first_queue(t_inputs *phs, t_thread_vars *thread_vars)
{
	pthread_mutex_lock(&phs->queue_mutex);
	phs->queue[thread_vars->pos][0] = phs->queue[thread_vars->pos][1];
	pthread_mutex_unlock(&phs->queue_mutex);
	phs->queue[thread_vars->pos][1] = 0;
}

