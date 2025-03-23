/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:25 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/23 13:36:27 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_inputs
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*forks_mute;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	mute_position;
	pthread_mutex_t	queue_mutex;
	int				n_philos;
	long			ttd;
	long			tte;
	long			tts;
	int				num_eat;
	int				is_num_eat;
	int				total_queue;
	int				*is_muted;
	int				*ph_pos;
	int				is_dead;
	int				**queue;
	struct timeval	init_time;
}	t_inputs;

typedef struct s_tv
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
}	t_tv;

// ph_check_user_input.c
int		ph_isdigit(int c);
int		is_non_zero_num(char *str);
int		ph_check_user_input(int argc, char **argv);

// ph_lock_unlock_forks.c
void	lock_fork(t_inputs *phs, t_tv *tv, int fork_pos);
int		ph_lock_forks(t_inputs *phs, t_tv *tv);
void	unlock_fork(t_inputs *phs, int fork_pos);
int		ph_unlock_forks(t_inputs *phs, t_tv *tv);

// ph_mem_management.c
void	ph_free_double_arr(int ***arr, int len);
void	ph_destroy_mutexes(t_inputs *phs);
void	ph_free_memory(t_inputs *phs);

// ph_prints.c
void	ph_print_time(t_inputs *phs, t_tv *tv, char *str);

// ph_queues.c
int		ph_set_queue(t_inputs *phs, int pos, t_tv *tv);
int		ph_set_queue_2(t_inputs *phs, t_tv *tv);
void	ph_remove_first_queue(t_inputs *phs, t_tv *tv);

// ph_set_philo_param.c
void	set_philosopher_position(t_inputs *phs, t_tv *tv);
void	set_philosopher_forks(t_inputs *phs, t_tv *tv);
int		ph_initialize_mutexes(t_inputs *phs);
void	initialize_tv(t_inputs *phs, t_tv *tv);

// ph_set_user_input_2.c
int		ph_isspace(char c);
int		ph_atoi(const char *nptr);
int		ph_set_int_zero(int **nums, int len);
int		free_t_inputs(t_inputs *crit);
int		ph_allocate_queue(t_inputs *crit);

// ph_set_user_input.c
int		ph_set_user_inputs_helper(t_inputs *crit);
int		ph_set_user_inputs(t_inputs *crit, char **argv);

// ph_threads_1.c
void	philo_thread_cycles(t_inputs *phs, t_tv *tv);
void	*philo_thread(void *arg);
void	*one_philosopher(void *arg);
int		create_and_join_threads(pthread_t *philos, t_inputs *crit);

// ph_threads_helper_2.c
void	lock_forks_mutex(t_inputs *phs, t_tv *tv);
void	unlock_forks_mutex(t_inputs *phs, t_tv *tv);

// ph_threads_helper.c
int		philo_eat_loop(t_inputs *phs, t_tv *tv, long utime);
int		philo_sleep_loop(t_inputs *phs, t_tv *tv, long utime);
int		philo_thinking_helper(t_inputs *phs, t_tv *tv, int *l_fp, int *r_fp);
int		philo_thinking(t_inputs *phs, t_tv *tv);

// ph_time_calc.c
long	return_time_microsec(struct timeval start, struct timeval end);

// philo_life_status.c
int		has_philosopher_died(t_inputs *phs);
int		is_philo_dead_of_hunger(t_inputs *phs, t_tv *tv);
int		check_philo_life_status(t_inputs *phs, t_tv *tv);

#endif
