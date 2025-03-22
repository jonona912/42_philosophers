/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:57:58 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:55:26 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ph_print_time(t_inputs *phs, t_tv *tv, char *str)
{
	gettimeofday(&tv->current_time, NULL);
	pthread_mutex_lock(&phs->print);
	printf("%ld %d %s\n", return_time_microsec(phs->init_time, tv->current_time) / 1000, tv->pos + 1, str);
	pthread_mutex_unlock(&phs->print);
}
