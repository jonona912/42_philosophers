/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:55:53 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/04 22:12:42 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_crits(t_inputs crit);

long	return_time_ms(struct timeval start, struct timeval end)
{
	return ((end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000));
}

void	*philosopher_activity(void *arg)
{
	t_inputs *phs = (t_inputs *)arg;
	struct timeval time;
	struct timeval init_time;
	int i;
	printf("Num: %ld\n", phs->tts);
	gettimeofday(&init_time, NULL);
	i = 0;
	while (i < phs->num_eat)
	{
		gettimeofday(&time, NULL);
		// if fork is free take a grab of something else wait (while loop)
		printf("%04ld %d has taken a fork\n", return_time_ms(init_time, time), 1);
		// usleep(phs->tte);
		gettimeofday(&time, NULL);
		printf("%ld %d is eating\n", return_time_ms(init_time, time), 1);
		usleep(phs->tte);
		gettimeofday(&time, NULL);
		printf("%ld %d is sleeping\n", return_time_ms(init_time, time), 1);
		usleep(phs->tts);
		if (phs->is_num_eat)
			i++;
	}
	return (NULL);
}

int	ph_set_queue(t_inputs *phs, int pos)
{
	int	i;

	i = 0;
	while (i < phs->num_p)
	{
		if (*(phs->queue + i) == 0)
		{
			*(phs->queue + i) = pos;
			return (1);
		}
		i++;
	}
	return (0);
}

void	int_swap(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

int	ph_remove_queue(t_inputs *phs, int pos)
{
	int	i;

	i = 0;
	while (i < phs->num_p)
	{
		if (*(phs->queue + i) == pos)
		{
			*(phs->queue + i) = 0;
			break;
		}
		i++;
	}
	while (i < phs->num_p - 1)
	{
		int_swap(phs->queue + i, phs->queue + i + 1);
		i++;
	}
	return (1);
}

void *two_philos(void *arg)
{
	t_inputs *phs = (t_inputs *)arg;
	struct timeval	time;
	struct timeval	init_time;
	struct timeval	prev_time;
	int	i;
	int	pos;

	i = 0;
	while (i < phs->num_p)
	{
		if (!*(phs->ph_pos + i))
		{
			*(phs->ph_pos + i) = 1;
			break ;
		}
		i++;
	}
	pos = i;
	gettimeofday(&init_time, NULL); // error
	i = 0;
	int flag = 0;
	// printf("This is philosopher #: %d\n", pos);
	// set the que
	ph_set_queue(phs, pos);
	while (i < phs->num_eat) 
	{
		// choose fork first and last fork
			// if pos == 0 (1st) then first and last fork
			// else if pos == num_p then last and first fork
			// else fork to the left and right
		// choose middle forks
		// choose forks for the last philosopher
		while (1)
		{
			if (pos == 0 && phs->num_p > 1 && pos == *(phs->queue)) // // check if the opening is on waitlist 
			{
					// (right) first fork			// (left) last fork
				if (!*(phs->fork_mx + pos) && !*(phs->fork_mx + phs->num_p - 1))
				{
					ph_remove_queue(phs, pos);
					break ; // update the queue
				}
			}
			else if (pos == *(phs->queue))// else if the this pos is on the waitlist
			{
					// (right) first fork			// (left) last fork
				if (!*(phs->fork_mx + pos) && !*(phs->fork_mx + pos - 1))
				{
					ph_remove_queue(phs, pos);
					break ; // update the queue
				}
			}
			
		}
		if (phs->is_dead)
		{
			printf("Philosopher died %d\n", pos);
			return NULL;
		}
		*(phs->fork_mx + pos) = 1; // right fork
		if (pos == 0)
		{
			*(phs->fork_mx + pos) = 1;
			pthread_mutex_lock(phs->forks + phs->num_p - 1); // left fork
		}
		else
		{
			*(phs->fork_mx + pos - 1) = 1;
			pthread_mutex_lock(phs->forks + pos - 1);
		}
		pthread_mutex_lock(phs->forks + pos);
		gettimeofday(&time, NULL);
		// printf("1: %ld and 2: %d\n", return_time_ms(init_time, time), phs->ttd / 1000);
		printf("is_dead: %d: %d\n", flag, return_time_ms(prev_time, time) > phs->ttd / 1000);
		if ((!flag && return_time_ms(init_time, time) > phs->ttd / 1000))
		{
			// printf("is_dead: %d\n", phs->is_dead);
			*(phs->fork_mx) = 0;
			*(phs->fork_mx + 1) = 0;
			phs->is_dead = 1;
			printf("Philosopher died %d\n", pos);
			*(phs->fork_mx + pos) = 0; // right fork
			if (pos == 0)
			{
				*(phs->fork_mx + pos) = 0;
				pthread_mutex_unlock(phs->forks + phs->num_p - 1); // left fork
			}
			else
			{
				*(phs->fork_mx + pos - 1) = 0;
				pthread_mutex_unlock(phs->forks + pos - 1);
			}
			pthread_mutex_unlock(phs->forks + pos);
			// pthread_mutex_unlock(phs->forks);
			// pthread_mutex_unlock(phs->forks + 1);
			return NULL;
		}
		else if ((flag && return_time_ms(prev_time, time) > phs->ttd / 1000))
		{
			// printf("is_dead: %d\n", phs->is_dead);
			*(phs->fork_mx) = 0;
			*(phs->fork_mx + 1) = 0;
			phs->is_dead = 1;
			printf("Philosopher died %d\n", pos);
			*(phs->fork_mx + pos) = 0; // right fork
			if (pos == 0)
			{
				*(phs->fork_mx + pos) = 0;
				pthread_mutex_unlock(phs->forks + phs->num_p - 1); // left fork
			}
			else
			{
				*(phs->fork_mx + pos - 1) = 0;
				pthread_mutex_unlock(phs->forks + pos - 1);
			}
			pthread_mutex_unlock(phs->forks + pos);
			// pthread_mutex_unlock(phs->forks);
			// pthread_mutex_unlock(phs->forks + 1);
			return NULL;
		}
		// if fork is free take a grab of something else wait (while loop)
		printf("%04ld %d has taken a fork\n", return_time_ms(init_time, time), pos + 1);
		// usleep(phs->tte);
		gettimeofday(&time, NULL);
		printf("%ld %d is eating\n", return_time_ms(init_time, time), pos + 1);
		usleep(phs->tte);
		gettimeofday(&prev_time, NULL);
		printf("%ld %d is sleeping\n", return_time_ms(init_time, prev_time), pos + 1);
		*(phs->fork_mx + pos) = 0; // right fork
		if (pos == 0)
		{
			*(phs->fork_mx + pos) = 0;
			pthread_mutex_unlock(phs->forks + phs->num_p - 1); // left fork
		}
		else
		{
			*(phs->fork_mx + pos - 1) = 0;
			pthread_mutex_unlock(phs->forks + pos - 1);
		}
		pthread_mutex_unlock(phs->forks + pos);
		// pthread_mutex_unlock(phs->forks);
		// pthread_mutex_unlock(phs->forks + 1);
		// *(phs->fork_mx) = 0;
		// *(phs->fork_mx + 1) = 0;
		usleep(phs->tts);
		if (phs->is_num_eat)
			i++;
		flag = 1;
	}
	return (NULL);
}

// write a code that will create a thread for each philosopher
// and then join them all
// then free the memory
// then return 0
// then test the code
// then submit the code



int main(int argc, char **argv)
{
	t_inputs	crit;
	pthread_t *philos;
	int			i;
	if (ph_check_user_input(argc, argv) == -1)
		return (1);
	ph_set_user_inputs(&crit, argv);
	print_crits(crit);
	// // // create array of philosophers with their forks
	// struct timeval first_time;
	// struct timeval second_time;
	// gettimeofday(&first_time, NULL);
	// printf("tv_sec: %ld\n", first_time.tv_sec);
	// printf("tv_mcs: %ld\n", first_time.tv_usec);
	// usleep(10);
	// // struct timeval second_time;
	// gettimeofday(&second_time, NULL);
	// printf("tv_sec: %ld\n", second_time.tv_sec - first_time.tv_sec);
	// printf("tv_mcs: %ld\n", second_time.tv_usec - first_time.tv_usec);
	// struct timeval start, now;
	// gettimeofday(&start, NULL);
	// do {
	// 	gettimeofday(&now, NULL);
	// 	printf("loop: %ld\n", (now.tv_sec - start.tv_sec) * 1000000 + (now.tv_usec - start.tv_usec));
	// } while ((now.tv_sec - start.tv_sec) * 1000000 + (now.tv_usec - start.tv_usec) < 10);
	// printf("2_mcss: %ld\n", now.tv_usec - start.tv_usec);


	philos = (pthread_t *)malloc(sizeof(pthread_t) * crit.num_p);
	i = 0;
	while (i < crit.num_p)
		pthread_create((philos + i++), NULL, two_philos, &crit);
	i = 0;
	while (i < crit.num_p)
		pthread_join(*(philos + i++), NULL);
	// pthread_create(&philo_1, NULL, philosopher_activity, &crit);
	// pthread_create(&philo_2, NULL, philosopher_activity, &crit);
	// pthread_join(philo_1, NULL);
	// pthread_join(philo_2, NULL);
	return (0);
}


// int main(void)
// {
// 	t_inputs phs;

// 	phs.num_p = 4;
// 	phs.queue = (int *)malloc(4 * sizeof(int));
// 	int i = -1;
// 	while (++i < 4)
// 		printf("num%d: %d\n", i, *(phs.queue + i));
// 	*phs.queue = 4;
// 	*(phs.queue + 1) = 3;
// 	*(phs.queue + 2) = 2;
// 	*(phs.queue + 3) = 1;
// 	i = -1;
// 	while (++i < 4)
// 		printf("num%d: %d\n", i, *(phs.queue + i));
// 	ph_remove_queue(&phs, 4);
// 	ph_remove_queue(&phs, 2);
// 	i = -1;
// 	while (++i < 4)
// 		printf("num%d: %d\n", i, *(phs.queue + i));
// 	return (0);
// }


void	print_crits(t_inputs crit)
{
	printf("num_p: %d\n", crit.num_p);
	printf("ttd: %ld\n", crit.ttd);
	printf("tte: %ld\n", crit.tte);
	printf("tts: %ld\n", crit.tts);
	printf("num_eat: %d\n", crit.num_eat);
	printf("is_num_eat: %d\n", crit.is_num_eat);
}



// #include <stdio.h>
// #include <sys/time.h>
// #include <unistd.h>

// int main() {
//     struct timeval start, end;
//     long tts = 1000; // Sleep for 100 milliseconds (100,000 microseconds)

//     while (1) {
//         gettimeofday(&start, NULL); // Get start time
//         usleep(tts); // Sleep for the specified time
//         gettimeofday(&end, NULL); // Get end time

//         // Calculate elapsed time in milliseconds
//         long elapsed_seconds = end.tv_sec - start.tv_sec;
// 		printf("elapsed sec : %ld\n", elapsed_seconds);
//         long elapsed_microseconds = end.tv_usec - start.tv_usec;
//         long elapsed_milliseconds = (elapsed_seconds * 1000) + (elapsed_microseconds / 1000);

//         printf("philosopher slept %ld milliseconds\n", elapsed_milliseconds);
//     }

//     return 0;
// }
