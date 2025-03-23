/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:22:10 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/23 12:15:40 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	return_time_microsec(struct timeval start, struct timeval end)
{
	return ((end.tv_sec * 1000000 + end.tv_usec)
		- (start.tv_sec * 1000000 + start.tv_usec));
}
