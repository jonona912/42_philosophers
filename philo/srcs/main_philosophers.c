/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:55:53 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/10 17:47:24 by zkhojazo         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_inputs	crit;
	pthread_t *philos;
	int			i;
	if (ph_check_user_input(argc, argv) == -1)
		return (1);
	ph_set_user_inputs(&crit, argv);
	// print_crits(crit);
	philos = (pthread_t *)malloc(sizeof(pthread_t) * crit.n_philos);
	i = 0;
	// initialize the forks
	while (i < crit.n_philos)
	{
		pthread_mutex_init(crit.forks + i, NULL);
		i++;
	}
	i = 0;
	gettimeofday(&crit.init_time, NULL);
	if (crit.n_philos == 1)
	{
		// pthread_mutex_init(crit.forks, NULL);
		pthread_create(philos, NULL, philosopher_activity, &crit);
		pthread_join(*philos, NULL);
	}
	else
	{
		while (i < crit.n_philos)
			pthread_create((philos + i++), NULL, even_num_philos, &crit);
		i = 0;
		while (i < crit.n_philos)
			pthread_join(*(philos + i++), NULL);
	}
	return (0);
} 

void	print_crits(t_inputs crit)
{
	printf("n_philos: %d\n", crit.n_philos);
	printf("ttd: %ld\n", crit.ttd);
	printf("tte: %ld\n", crit.tte);
	printf("tts: %ld\n", crit.tts);
	printf("num_eat: %d\n", crit.num_eat);
	printf("is_num_eat: %d\n", crit.is_num_eat);
}
