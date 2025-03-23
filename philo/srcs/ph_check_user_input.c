/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check_user_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:58:48 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/03/23 13:18:03 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ph_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_non_zero_num(char *str)
{
	int	non_zero_digit;

	non_zero_digit = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (!ph_isdigit(*str))
			return (0);
		if (*str != '0')
			non_zero_digit = 1;
		str++;
	}
	return (non_zero_digit);
}

int	ph_check_user_input(int argc, char **argv)
{
	int	i;

	if (argc < 5)
	{
		printf("Insufficient number of arguments. Try again\n");
		return (-1);
	}
	else if (argc > 6)
	{
		printf("Too many arguments. Try again\n");
		return (-1);
	}
	i = 1;
	while (*(argv + i))
	{
		if (!is_non_zero_num(*(argv + i)))
		{
			printf("Wrong input. Inputs must be non zero number\n");
			return (-1);
		}
		i++;
	}
	return (0);
}
