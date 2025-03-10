/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:39:39 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/10 23:09:28 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*
 * This function sets the position of a philosopher.
 * It initializes the index, finds an available philosopher position,
 * marks the position as taken, and sets the philosopher's position.
 */
void	set_philosopher_position(t_inputs *phs, t_thread_vars *thread_vars)
{
	int i = 0;

	while (i < phs->n_philos)
	{
		if (!*(phs->ph_pos + i))
		{
			*(phs->ph_pos + i) = 1;
			break;
		}
		i++;
	}
	thread_vars->pos = i;
}

void	set_philosopher_forks(t_inputs *phs, t_thread_vars *thread_vars)
{
	if (thread_vars->pos == 0)
	{
		thread_vars->left_fork_pos = phs->n_philos - 1;
		thread_vars->right_fork_pos = thread_vars->pos;
	}
	else
	{
		thread_vars->left_fork_pos = thread_vars->pos - 1;
		thread_vars->right_fork_pos = thread_vars->pos;
	}
}

// send philosopher to think
int	philo_thinking(t_inputs *phs, t_thread_vars *thread_vars)
{
	int	num_forks_picked;

	num_forks_picked = 0;
	// check every 10 ms if a philosopher died, if not then grab two forks
	gettimeofday(&phs->time, NULL);
	printf("%ld %d is thinking\n", return_time_ms(phs->init_time, phs->time), thread_vars->pos + 1);
	while (1)
	{
		gettimeofday(&phs->time, NULL);
		if (phs->is_dead)
		{
			printf("%ld %d died\n", return_time_ms(phs->init_time, phs->time), thread_vars->pos + 1);
			// printf("Philosopher died %d\n", thread_vars->pos);
			return (-1);
		}
		// check if left and right fork are free and the pos is in queue and free them
		// check whether current philo is in queue and left and right fork are free
		if (thread_vars->pos == phs->queue[thread_vars->pos][0] && !phs->is_muted[thread_vars->left_fork_pos])
		{
			pthread_mutex_lock(phs->forks + thread_vars->left_fork_pos);
			printf("%ld %d has taken a fork\n", return_time_ms(phs->init_time, phs->time), thread_vars->pos + 1);
			phs->is_muted[thread_vars->left_fork_pos] = 1;
			num_forks_picked++;
		}
		if (thread_vars->pos == phs->queue[thread_vars->pos][0] && !phs->is_muted[thread_vars->right_fork_pos])
		{
			pthread_mutex_lock(phs->forks + thread_vars->right_fork_pos);
			printf("%ld %d has taken a fork\n", return_time_ms(phs->init_time, phs->time), thread_vars->pos + 1);
			phs->is_muted[thread_vars->right_fork_pos] = 1;
			num_forks_picked++;
		}
		if (num_forks_picked == 2)
		{
			ph_remove_first_queue(phs, thread_vars);
			break ;
		}
		if (return_time_ms(phs->init_time, phs->time) < phs->tte)
			usleep(9000);
	}
	return (0);
}


int is_time_less_than(struct timeval prev_time, struct timeval current_time, long time, long interval)
{
	long time_diff;

	gettimeofday(&current_time, NULL);
	// prev_time - current_time - time
	time_diff = return_time_ms(prev_time, current_time);
	if (time_diff <= time)
	{
		time_diff = time - time_diff;
		return (time_diff < interval);
	}
	else
		return (0);
}

int	philosopher_sleep_and_think(t_inputs *phs, t_thread_vars *thread_vars)
{
	ph_set_queue(phs, thread_vars->pos);
	gettimeofday(&thread_vars->current_time, NULL);
	printf("%ld %d is sleeping\n", return_time_ms(phs->init_time, thread_vars->current_time), thread_vars->pos + 1);
	while (is_time_less_than(phs->time, 9))
	{
		if (phs->is_dead)
		{
			printf("%ld %d died\n", return_time_ms(phs->init_time, phs->time), thread_vars->pos + 1);
			return (-1);
		}
		usleep(9000);
	}
	// usleep(phs->tts);
	philo_thinking(phs, thread_vars);
	return (0);
}

int	philosopher_eating(t_inputs *phs, t_thread_vars *thread_vars)
{
	printf("%ld %d is eating\n", return_time_ms(phs->init_time, phs->time), thread_vars->pos + 1);
	// logic to sleep 9 ms or less than time remaining to eat
	
	usleep(phs->tte);
	gettimeofday(&thread_vars->time_ate, NULL);
}

void	even_num_philos_cycles(t_inputs *phs, t_thread_vars *thread_vars)
{
	while (thread_vars->i < phs->num_eat)
	{
		gettimeofday(&phs->time, NULL);
		// printf("%ld %d is eating\n", return_time_ms(phs->init_time, phs->time), thread_vars->pos + 1);
		// usleep(phs->tte);
		// gettimeofday(&thread_vars->time_finished_eating, NULL);
		// thread_vars->ate = 1;
		pthread_mutex_unlock(phs->forks + thread_vars->right_fork_pos); // equivalent of right_fork
		phs->is_muted[thread_vars->right_fork_pos] = 0;
		pthread_mutex_unlock(phs->forks + thread_vars->left_fork_pos); // equivalent of left_fork
		phs->is_muted[thread_vars->left_fork_pos] = 0;
		philosopher_sleep_and_think(phs, thread_vars);
		if (phs->is_num_eat)
			thread_vars->i++;
	}
}

void initialize_thread_vars(t_thread_vars *thread_vars)
{
	memset(&thread_vars->time_thought, 0, sizeof(struct timeval));
	memset(&thread_vars->time_ate, 0, sizeof(struct timeval));
	memset(&thread_vars->time_woke_up, 0, sizeof(struct timeval));
	memset(&thread_vars->current_time, 0, sizeof(struct timeval));
	thread_vars->left_fork_pos = 0;
	thread_vars->right_fork_pos = 0;
	thread_vars->pos = 0;
	thread_vars->i = 0;
	thread_vars->flag = 0;
}

// even num of philosophers
void	*even_num_philos(void *arg)
{
	// if the number of a philosopher is even then make it eat
	t_inputs *phs = (t_inputs *)arg;
	t_thread_vars	thread_vars;

	initialize_thread_vars(&thread_vars);
	set_philosopher_position(phs, &thread_vars);
	set_philosopher_forks(phs, &thread_vars);
	gettimeofday(&phs->time, NULL);
	gettimeofday(&thread_vars.time_ate, NULL);
	if ((thread_vars.pos + 1)% 2 == 1)
	{
		philosopher_sleep_and_think(phs, &thread_vars);
	}
	else
	{
		pthread_mutex_lock(phs->forks + thread_vars.left_fork_pos);
		printf("%ld %d has taken a fork\n", return_time_ms(phs->init_time, phs->time), thread_vars.pos + 1);
		pthread_mutex_lock(phs->forks + thread_vars.right_fork_pos);
		gettimeofday(&phs->time, NULL);
		printf("%ld %d has taken a fork\n", return_time_ms(phs->init_time, phs->time), thread_vars.pos + 1);
	}
	even_num_philos_cycles(phs, &thread_vars);
	return (NULL);
}


	// while thinking the philosopher checks whether the fork is free


	// if odd send it to think
	// no need for queue - just wait for the fork to free
	// if the fork is free then lock it and eat

