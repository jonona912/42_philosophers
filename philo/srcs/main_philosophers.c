/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:55:53 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:23:19 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_crits(t_inputs crit);
void	*philosopher_activity(void *arg);

int main(int argc, char **argv)
{
	t_inputs	crit;
	pthread_t	*philos;

	if (ph_check_user_input(argc, argv) == -1)
		return (1);
	if (ph_set_user_inputs(&crit, argv) == -1)
		return (printf("Memory allocation failed\n"), -1);
	philos = (pthread_t *)malloc(sizeof(pthread_t) * crit.n_philos);
	if (ph_initialize_mutexes(&crit) == -1)
		return (printf("Mutex init failed\n"), 1);
	gettimeofday(&crit.init_time, NULL);
	if (create_and_join_threads(philos, &crit) == -1)
		return (printf("Thread creation failed\n"), 1);
	ph_free_memory(&crit);
	free(philos);
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
