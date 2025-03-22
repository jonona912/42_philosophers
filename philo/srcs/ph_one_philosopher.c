/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_one_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:07:21 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/22 23:55:26 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philosopher_activity(void *arg)
{
	t_tv	tv;
	t_inputs 		*phs;

	phs	= (t_inputs *)arg;
	initialize_tv(phs, &tv);
	set_philosopher_position(phs, &tv);
	ph_print_time(phs, &tv, "has taken a fork");
	usleep(phs->ttd);
	ph_print_time(phs, &tv, "died");
	return (NULL);
}
