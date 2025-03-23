/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_set_user_input_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:20:46 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/23 13:21:03 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ph_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ph_atoi(const char *nptr)
{
	int	acum;
	int	sign;

	sign = 1;
	acum = 0;
	while (ph_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ph_isdigit(*nptr))
	{
		acum = acum * 10 + (*nptr - '0');
		nptr++;
	}
	nptr--;
	return (acum * sign);
}

int	ph_set_int_zero(int **nums, int len)
{
	int	i;

	if (!nums || !*nums)
		return (0);
	i = 0;
	while (i < len)
		*((*nums) + i++) = 0;
	return (1);
}

int	free_t_inputs(t_inputs *crit)
{
	if (crit->forks)
	{
		free(crit->forks);
		crit->forks = NULL;
	}
	if (crit->is_muted)
	{
		free(crit->is_muted);
		crit->is_muted = NULL;
	}
	if (crit->ph_pos)
	{
		free(crit->ph_pos);
		crit->ph_pos = NULL;
	}
	if (crit->queue)
	{
		free (crit->queue);
		crit->queue = NULL;
	}
	return (1);
}

int	ph_allocate_queue(t_inputs *crit)
{
	int	i;

	i = 0;
	crit->queue = (int **)malloc(crit->n_philos * sizeof(int *));
	if (!crit->queue)
		return (free_t_inputs(crit), -1);
	while (i < crit->n_philos)
	{
		*(crit->queue + i) = (int *)malloc(2 * sizeof(int));
		if (!*(crit->queue + i))
		{
			while (i >= 0)
				free(*(crit->queue + i--));
			return (free_t_inputs(crit), -1);
		}
		ph_set_int_zero((crit->queue + i), 2);
		i++;
	}
	return (1);
}
