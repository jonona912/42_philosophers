/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:55:53 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/08 20:58:11 by zkhojazo         ###   ########.fr       */
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

// int	ph_set_queue(t_inputs *phs, int pos)
// {
// 	int	i;

// 	i = 0;
// 	// pthread_mutex_lock(phs->queue);
// 	while (i < phs->n_philos)
// 	{
// 		if (*(phs->queue + i) == 0)
// 		{
// 			*(phs->queue + i) = pos;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	// pthread_mutex_unlock(phs->queue);
// 	return (0);
// }

// void	int_swap(int *a, int *b)
// {
// 	*a = *a ^ *b;
// 	*b = *a ^ *b;
// 	*a = *a ^ *b;
// }

// int	ph_remove_queue(t_inputs *phs, int pos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < phs->n_philos)
// 	{
// 		if (*(phs->queue + i) == pos)
// 		{
// 			*(phs->queue + i) = 0;
// 			break;
// 		}
// 		i++;
// 	}
// 	while (i < phs->n_philos - 1)
// 	{
// 		int_swap(phs->queue + i, phs->queue + i + 1);
// 		i++;
// 	}
// 	return (1);
// }

// void	*two_philos(void *arg)
// {
// 	t_inputs *phs = (t_inputs *)arg;
// 	struct timeval	time;
// 	struct timeval	init_time;
// 	struct timeval	prev_time;
// 	int	i;
// 	int	pos;

// 	i = 0;
// 	while (i < phs->n_philos)
// 	{
// 		if (!*(phs->ph_pos + i))
// 		{
// 			*(phs->ph_pos + i) = 1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	pos = i;
// 	gettimeofday(&init_time, NULL); // error
// 	i = 0;
// 	int flag = 0;
// 	// printf("This is philosopher #: %d\n", pos);
// 	// set the que
// 	ph_set_queue(phs, pos);
// 	while (i < phs->num_eat) 
// 	{
// 		// choose fork first and last fork
// 			// if pos == 0 (1st) then first and last fork
// 			// else if pos == n_philos then last and first fork
// 			// else fork to the left and right
// 		// choose middle forks
// 		// choose forks for the last philosopher
// 		while (1)
// 		{
// 			if (pos == 0 && phs->n_philos > 1 && pos == *(phs->queue)) // // check if the opening is on waitlist 
// 			{
// 					// (right) first fork			// (left) last fork
// 				if (!*(phs->is_muted + pos) && !*(phs->is_muted + phs->n_philos - 1))
// 				{
// 					ph_remove_queue(phs, pos);
// 					break ; // update the queue
// 				}
// 			}
// 			else if (pos == *(phs->queue))// else if the this pos is on the waitlist
// 			{
// 					// (right) first fork			// (left) last fork
// 				if (!*(phs->is_muted + pos) && !*(phs->is_muted + pos - 1))
// 				{
// 					ph_remove_queue(phs, pos);
// 					break ; // update the queue
// 				}
// 			}
// 		}
// 		if (phs->is_dead)
// 		{
// 			printf("Philosopher died %d\n", pos);
// 			return NULL;
// 		}
// 		*(phs->is_muted + pos) = 1; // right fork
// 		if (pos == 0)
// 		{
// 			*(phs->is_muted + pos) = 1;
// 			pthread_mutex_lock(phs->forks + phs->n_philos - 1); // left fork
// 		}
// 		else
// 		{
// 			*(phs->is_muted + pos - 1) = 1;
// 			pthread_mutex_lock(phs->forks + pos - 1);
// 		}
// 		pthread_mutex_lock(phs->forks + pos);
// 		gettimeofday(&time, NULL);
// 		// printf("1: %ld and 2: %d\n", return_time_ms(init_time, time), phs->ttd / 1000);
// 		printf("is_dead: %d: %d\n", flag, return_time_ms(prev_time, time) > phs->ttd / 1000);
// 		if ((!flag && return_time_ms(init_time, time) > phs->ttd / 1000))
// 		{
// 			// printf("is_dead: %d\n", phs->is_dead);
// 			*(phs->is_muted) = 0;
// 			*(phs->is_muted + 1) = 0;
// 			phs->is_dead = 1;
// 			printf("Philosopher died %d\n", pos);
// 			*(phs->is_muted + pos) = 0; // right fork
// 			if (pos == 0)
// 			{
// 				*(phs->is_muted + pos) = 0;
// 				pthread_mutex_unlock(phs->forks + phs->n_philos - 1); // left fork
// 			}
// 			else
// 			{
// 				*(phs->is_muted + pos - 1) = 0;
// 				pthread_mutex_unlock(phs->forks + pos - 1);
// 			}
// 			pthread_mutex_unlock(phs->forks + pos);
// 			// pthread_mutex_unlock(phs->forks);
// 			// pthread_mutex_unlock(phs->forks + 1);
// 			return NULL;
// 		}
// 		else if ((flag && return_time_ms(prev_time, time) > phs->ttd / 1000))
// 		{
// 			// printf("is_dead: %d\n", phs->is_dead);
// 			*(phs->is_muted) = 0;
// 			*(phs->is_muted + 1) = 0;
// 			phs->is_dead = 1;
// 			printf("Philosopher died %d\n", pos);
// 			*(phs->is_muted + pos) = 0; // right fork
// 			if (pos == 0)
// 			{
// 				*(phs->is_muted + pos) = 0;
// 				pthread_mutex_unlock(phs->forks + phs->n_philos - 1); // left fork
// 			}
// 			else
// 			{
// 				*(phs->is_muted + pos - 1) = 0;
// 				pthread_mutex_unlock(phs->forks + pos - 1);
// 			}
// 			pthread_mutex_unlock(phs->forks + pos);
// 			// pthread_mutex_unlock(phs->forks);
// 			// pthread_mutex_unlock(phs->forks + 1);
// 			return NULL;
// 		}
// 		// if fork is free take a grab of something else wait (while loop)
// 		printf("%04ld %d has taken a fork\n", return_time_ms(init_time, time), pos + 1);
// 		// usleep(phs->tte);
// 		gettimeofday(&time, NULL);
// 		printf("%ld %d is eating\n", return_time_ms(init_time, time), pos + 1);
// 		usleep(phs->tte);
// 		gettimeofday(&prev_time, NULL);
// 		printf("%ld %d is sleeping\n", return_time_ms(init_time, prev_time), pos + 1);
// 		*(phs->is_muted + pos) = 0; // right fork
// 		if (pos == 0)
// 		{
// 			*(phs->is_muted + pos) = 0;
// 			pthread_mutex_unlock(phs->forks + phs->n_philos - 1); // left fork
// 		}
// 		else
// 		{
// 			*(phs->is_muted + pos - 1) = 0;
// 			pthread_mutex_unlock(phs->forks + pos - 1);
// 		}
// 		pthread_mutex_unlock(phs->forks + pos);
// 		// pthread_mutex_unlock(phs->forks);
// 		// pthread_mutex_unlock(phs->forks + 1);
// 		// *(phs->is_muted) = 0;
// 		// *(phs->is_muted + 1) = 0;
// 		usleep(phs->tts);
// 		if (phs->is_num_eat)
// 			i++;
// 		flag = 1;
// 	}
// 	return (NULL);
// }

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


	philos = (pthread_t *)malloc(sizeof(pthread_t) * crit.n_philos);
	i = 0;
	// initialize the forks
	while (i < crit.n_philos)
	{
		pthread_mutex_init(crit.forks + i, NULL);
		i++;
	}
	i = 0;
	if (crit.n_philos % 2 == 0)
	{
		while (i < crit.n_philos)
			pthread_create((philos + i++), NULL, even_num_philos, &crit);
	}
	else
	{
		printf("Odd number of philosophers\n");
	}
	i = 0;
	while (i < crit.n_philos)
		pthread_join(*(philos + i++), NULL);
	return (0);
}

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// void* thread_function(void* arg) {
//     pthread_mutex_lock(&mutex); // Try to lock the mutex
//     printf("Thread %ld has the lock\n", (long)arg);
//     sleep(2); // Simulate some work
//     pthread_mutex_unlock(&mutex); // Unlock the mutex
//     return NULL;
// }

// int main() {
//     pthread_t thread1, thread2;

//     pthread_create(&thread1, NULL, thread_function, (void*)1);
//     pthread_create(&thread2, NULL, thread_function, (void*)2);

//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);

//     return 0;
// }

void	print_crits(t_inputs crit)
{
	printf("n_philos: %d\n", crit.n_philos);
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
//         long elapsed_seconds = end.thread_vars_sec - start.thread_vars_sec;
// 		printf("elapsed sec : %ld\n", elapsed_seconds);
//         long elapsed_microseconds = end.thread_vars_usec - start.thread_vars_usec;
//         long elapsed_milliseconds = (elapsed_seconds * 1000) + (elapsed_microseconds / 1000);

//         printf("philosopher slept %ld milliseconds\n", elapsed_milliseconds);
//     }

//     return 0;
// }
