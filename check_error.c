/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:51:50 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/02/19 00:39:32 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	strtol_errorcheck(char *str, long check_num)
{
	long	num;
	long	flag;

	num = 0;
	flag = 1;
	if (*str == '-')
	{
		if (check_num >= 0)
			return (1);
		str++;
		flag = -1;
	}
	while (*str)
	{
		num = num * 10 + (long)(*str - '0');
		str++;
	}
	num = num * flag;
	if (check_num != num)
		return (1);
	return (0);
}

int	argvcheck(char *str)
{
	if (*str == '-')
	{
		str++;
		if (!(*str >= '0' && *str <= '9') || *str == '0')
			return (1);
	}
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (1);
		str++;
	}
	return (0);
}

int	ret_error(char *str)
{
	if (str)
		printf("Error : %s\n", str);
	else
		printf("Error\n");
	return (1);
}
