/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:25 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/08 18:08:50 by zkhojazo         ###   ########.fr       */
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
	int		n_philos;
	long	ttd;
	long	tte;
	long	tts;
	int		num_eat;
	int		is_num_eat;
	// create philosophers array
	pthread_mutex_t	*forks;
	int		total_queue;
	int		*is_muted;
	int		*ph_pos;
	// create keys
	int		is_dead; // if one dies simulation stops
	int		**queue;
}	t_inputs;

typedef struct s_thread_vars
{
	struct timeval	time;
	struct timeval	init_time;
	struct timeval	prev_time;
	int				left_fork_pos;
	int				right_fork_pos;
	int				pos;
	int				i;
	int				flag;
}	t_thread_vars;

typedef enum s_lock_status
{
	LOCKED,
	UNLOCKED
}	t_lock_status;


// // ph_check_user_input.c
// int	ph_isdigit(int c);
// int	is_num(char *str);
// int	ph_check_user_input(int argc, char **argv);

// // ph_set_user_input.c
// int	ph_isspace(char c);
// int	ph_atoi(const char *nptr);
// int	ph_set_user_inputs(t_inputs *crit, char **argv);

// // ph_queues.c
// int	ph_set_queue(t_inputs *phs, int pos);
// void	ph_remove_first_queue(t_inputs *phs, t_thread_vars *thread_vars);




// Function prototypes

// main_philosophers.c
void	print_crits(t_inputs crit);
long	return_time_ms(struct timeval start, struct timeval end);
void	*philosopher_activity(void *arg);
void	*two_philos(void *arg);

// ph_check_user_input.c
int	ph_isdigit(int c);
int	is_num(char *str);
int	ph_check_user_input(int argc, char **argv);

// ph_set_user_input.c
int	ph_isspace(char c);
int	ph_atoi(const char *nptr);
int	ph_set_user_inputs(t_inputs *crit, char **argv);

// ph_queues.c
int	ph_set_queue(t_inputs *phs, int pos);
void	ph_remove_first_queue(t_inputs *phs, t_thread_vars *thread_vars);

// ph_threads_1.c
void	set_philosopher_position(t_inputs *phs, t_thread_vars *thread_vars);
void	wait_for_forks(t_inputs *phs, t_thread_vars *thread_vars);
void	lock_forks(t_inputs *phs, t_thread_vars *thread_vars, t_lock_status status);

// ph_threads_2.c
void	set_philosopher_forks(t_inputs *phs, t_thread_vars *thread_vars);
int		philo_thinking(t_inputs *phs, t_thread_vars *thread_vars);
void	*even_num_philos(void *arg);

#endif
