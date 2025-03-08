/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_queues.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:09:14 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/08 21:01:01 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ph_set_queue(t_inputs *phs, int pos)
{
	int	i;

	i = 0;
	while (i < phs->total_queue)
	{
		if (phs->queue[pos][i] == 0)
		{
			*(*(phs->queue + pos) + i) = pos;
			break;
		}
		i++;
	}
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
	phs->queue[thread_vars->pos][0] = phs->queue[thread_vars->pos][1];
	phs->queue[thread_vars->pos][1] = 0;
}

