/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_others.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:09:46 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/11/07 17:29:54 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	calc_time(void)
{
	struct timeval	time;
	long			actual_time;

	gettimeofday(&time, NULL);
	actual_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (actual_time);
}

void	print_message(char *str, t_info *info, int id)
{
	long	actual_time;

	actual_time = calc_time () - info->time_start;
	if (!is_some_dead(info))
	{
		pthread_mutex_lock(&(info)->mutex_msg);
		printf("[%03ld] [%d] %s\n", actual_time, id + 1, str);
		pthread_mutex_unlock(&(info)->mutex_msg);
	}
}

void	set_life(t_info *info, int is_dead, int id)
{
	pthread_mutex_lock(&info->mutex_is_dead[id]);
	info->philo[id].is_dead = is_dead;
	pthread_mutex_unlock(&info->mutex_is_dead[id]);
	if (is_dead == 1)
	{
		pthread_mutex_lock(&info->mutex_state);
		pthread_mutex_lock(&info->mutex_msg);
		info->is_some_dead = 1;
		pthread_mutex_unlock(&info->mutex_msg);
		pthread_mutex_unlock(&info->mutex_state);
	}
}

void	to_wait(long time)
{
	long	actual_time;

	actual_time = calc_time() + time;
	while (actual_time > calc_time())
	{
		usleep(100);
	}
}

void	to_wait_to_eat(long time)
{
	while (calc_time() < time)
	{
		usleep(50);
	}
}
