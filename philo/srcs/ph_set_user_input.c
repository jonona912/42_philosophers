/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_set_user_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:03:13 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:22:24 by zkhojazo         ###   ########.fr       */
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
	int i;

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

int	ph_set_user_inputs_helper(t_inputs *crit)
{
	int	i;

	i = 0;
	crit->forks = (pthread_mutex_t *)malloc(crit->n_philos * sizeof(pthread_mutex_t));
	crit->forks_mute = (pthread_mutex_t *)malloc(crit->n_philos * sizeof(pthread_mutex_t)); // problem if fail, return error
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
	// crit->queue = (int **)malloc(crit->n_philos * sizeof(int *));
	// if (!crit->queue)
	// 	return (free_t_inputs(crit), -1);
	// while (i < crit->n_philos)
	// {
	// 	*(crit->queue + i) = (int *)malloc(2 * sizeof(int));
	// 	if (!*(crit->queue + i))
	// 		return (free_t_inputs(crit), 0); // if malloc fails free all the previous mallocs
	// 	ph_set_int_zero((crit->queue + i), 2);
	// 	i++;
	// }
	return (1);
}

int	ph_set_user_inputs(t_inputs *crit, char **argv)
{
	int	i;

	i = 0;
	crit->n_philos = ph_atoi(*(argv + ++i));
	if (crit->n_philos > 200)
		return (printf("Number of philosophers must be less than 200\n"), -1);
	crit->ttd = ph_atoi(*(argv + ++i)) * 1000; // 1 micor second == 1000 millisocnd (for usleep)
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
