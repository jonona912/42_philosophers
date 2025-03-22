/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_queues.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:09:14 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:55:26 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ph_set_queue(t_inputs *phs, int pos, t_tv *tv)
{
	int	i;

	i = 0;
	while (i < phs->total_queue)
	{
		if (phs->queue[pos][i] == 0)
		{
			*(*(phs->queue + pos) + i) = tv->pos + 1;
			break;
		}
		i++;
	}
	return (1);
}

int	ph_set_queue_2(t_inputs *phs, t_tv *tv)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&phs->queue_mutex);
	ph_set_queue(phs, tv->left_fork_pos, tv);
	ph_set_queue(phs, tv->right_fork_pos, tv);
	pthread_mutex_unlock(&phs->queue_mutex);
	return (1);
}

void	ph_remove_first_queue(t_inputs *phs, t_tv *tv)
{
	pthread_mutex_lock(&phs->queue_mutex);
	phs->queue[tv->left_fork_pos][0] = phs->queue[tv->left_fork_pos][1];
	phs->queue[tv->left_fork_pos][1] = 0;
	phs->queue[tv->right_fork_pos][0] = phs->queue[tv->right_fork_pos][1];
	phs->queue[tv->right_fork_pos][1] = 0;
	pthread_mutex_unlock(&phs->queue_mutex);
}
