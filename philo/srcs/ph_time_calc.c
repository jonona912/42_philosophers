/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:22:10 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/20 23:39:35 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	return_time_microsec(struct timeval start, struct timeval end)
{
	return ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
}

// int	is_time_less_than(struct timeval prev_time, long utime, long interval)
// {
// 	long			time_diff;
// 	struct timeval	current_time;

// 	gettimeofday(&current_time, NULL);
// 	// prev_time - current_time - utime
// 	time_diff = return_time_microsec(prev_time, current_time);
// 	utime /= 1000;
// 	printf("time_diff: %ld utime: %ld\n", time_diff, utime);
// 	if (time_diff <= utime)
// 	{
// 		time_diff = (utime - time_diff);
// 		printf("return: %d\n", (time_diff > interval));
// 		return (time_diff > interval);
// 	}
// 	else
// 		return (0);
// }

long	time_remaining_microsecond(struct timeval prev_time, long time)
{
	long time_diff;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	time_diff = (current_time.tv_sec - prev_time.tv_sec) * 1000000 + (current_time.tv_usec - prev_time.tv_usec);
	if (time_diff <= time)
		return (time - time_diff);
	else
		return (0);
}
