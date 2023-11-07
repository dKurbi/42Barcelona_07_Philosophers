/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_ft_atoi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:10:44 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/11/07 16:55:42 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

static int	initnum(const char *str, int *sign, int *number)
{
	int	i;

	*number = 0;
	i = 0;
	*sign = 1;
	while ((str[i] > 8 && str [i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		i++;
		*sign = -1;
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	sign;

	i = initnum(str, &sign, &n);
	while (str[i] && ft_isdigit(str[i]))
	{
		if (n > 214748364 || ((n == 214748364) && ((str[i] - '0') > 7)))
		{
			if (sign > 0)
				return (2147483647);
			else
				return (-2147483648);
		}
		else
			n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n * sign);
}
