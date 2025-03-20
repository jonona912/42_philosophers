/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:25 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/20 23:39:07 by zkhojazo         ###   ########.fr       */
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	*forks_mute;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	mute_position;
	pthread_mutex_t	queue_mutex; // not destroyed
	// pthread_mutex_t change_mute;
	int			n_philos;
	long		ttd;
	long		tte;
	long		tts;
	int			num_eat;
	int			is_num_eat;
	int			total_queue;
	int			*is_muted;
	int			*ph_pos;
	int			is_dead; // if one dies simulation stops
	int			**queue;
	struct timeval	init_time;
}	t_inputs;

typedef struct s_thread_vars
{
	struct timeval	time_thought;
	struct timeval	time_ate;
	struct timeval	prev_time;
	struct timeval	current_time;

	int				left_fork_pos;
	int				right_fork_pos;
	int				pos;
	int				i;
	int				flag;
	long			ttd_thread;
	long			tte_thread;
	long			tts_thread;
	int				num_eat_thread;
	int				is_num_eat_thread;
	long			sleep_interval;
}	t_thread_vars;

typedef enum s_lock_status
{
	LOCK,
	UNLOCK
}	t_lock_status;

typedef enum s_fork_lock
{
	LEFT_FORK,
	RIGHT_FORK,
	BOTH_FORKS
}	t_fork_lock;

// main_philosophers.c
void	print_crits(t_inputs crit);
void	*philosopher_activity(void *arg);
void	*two_philos(void *arg);

// ph_check_user_input.c
int	ph_isdigit(int c);
int	is_num(char *str);
int	ph_check_user_input(int argc, char **argv);

// ph_mem_management.c
void	ph_destroy_mutexes_and_free_queue(t_inputs *phs);
void	ph_free_memory(t_inputs *phs);

// ph_one_philosopher.c
void	one_philo_thinking(t_inputs *phs, t_thread_vars *thread_vars, long time_to_think);
void	*philosopher_activity(void *arg);

// ph_prints.c
void	ph_print_time(t_inputs *phs, t_thread_vars *thread_vars, char *str);

// ph_set_philo_param.c
void	set_philosopher_position(t_inputs *phs, t_thread_vars *thread_vars);
void	set_philosopher_forks(t_inputs *phs, t_thread_vars *thread_vars);
int	ph_initialize_mutexes(t_inputs *phs);
void	initialize_thread_vars(t_inputs *phs, t_thread_vars *thread_vars);

// ph_set_user_input.c
int	ph_isspace(char c);
int	ph_atoi(const char *nptr);
int	ph_set_user_inputs(t_inputs *crit, char **argv);

// ph_queues.c
int	ph_set_queue(t_inputs *phs, int pos);
void	ph_remove_first_queue(t_inputs *phs, t_thread_vars *thread_vars);

// ph_threads_1.c
int create_and_join_threads(pthread_t *philos, t_inputs *crit);
// void	wait_for_forks(t_inputs *phs, t_thread_vars *thread_vars);
// void	lock_forks(t_inputs *phs, t_thread_vars *thread_vars, t_lock_status status);

// ph_threads_2.c
void	set_philosopher_forks(t_inputs *phs, t_thread_vars *thread_vars);
int		philo_thinking(t_inputs *phs, t_thread_vars *thread_vars);
void	*more_than_one_philo(void *arg);
int	pick_a_fork(t_inputs *phs, t_thread_vars *thread_vars, int fork_pos);

// ph_threads_helper.c
// int	ph_unlock_forks(t_inputs *phs, t_thread_vars *thread_vars);
int	philo_eat_loop(t_inputs *phs, t_thread_vars *thread_vars, long utime);
int	philo_sleep_loop(t_inputs *phs, t_thread_vars *thread_vars, long utime);
int	philo_thinking(t_inputs *phs, t_thread_vars *thread_vars);

// ph_threads_helper_2.c
int ph_forks_mutex_change(t_inputs *phs, t_thread_vars *thread_vars, t_lock_status status);
int ph_lock_forks(t_inputs *phs, t_thread_vars *thread_vars);
int	ph_unlock_forks(t_inputs *phs, t_thread_vars *thread_vars);

// ph_time_calc.c
long	return_time_microsec(struct timeval start, struct timeval end);
// int	is_time_less_than(struct timeval prev_time, long time, long interval);
long	time_remaining_microsecond(struct timeval prev_time, long time);

#endif
