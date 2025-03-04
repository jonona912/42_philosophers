/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:25 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/04 12:58:11 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h> // for gettimeofday
#include <stdlib.h>

// number_of_philosophers 
// time_to_die 
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]
typedef struct s_inputs
{
	int		num_p;
	long	ttd;
	long	tte;
	long	tts;
	int		num_eat;
	int		is_num_eat;
	// create philosophers array
	pthread_mutex_t	*forks;
	int		*fork_mx;
	int		*ph_pos;
	// create keys
	int		is_dead; // if one dies simulation stops
	int		*queue;
}	t_inputs;

// typedef struct t_philosophers
// {
	
// }



// ph_check_user_input.c
int	ph_isdigit(int c);
int	is_num(char *str);
int	ph_check_user_input(int argc, char **argv);

// ph_set_user_input.c
int	ph_isspace(char c);
int	ph_atoi(const char *nptr);
int	ph_set_user_inputs(t_inputs *crit, char **argv);


#endif
