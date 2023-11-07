/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_check_dead.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:44:41 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/11/07 17:54:03 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*is_alive(void *arg)
{
	int		i;
	t_info	*info;

	info = (t_info *) arg;
	pthread_mutex_lock(&info->mutex_start);
	pthread_mutex_unlock(&info->mutex_start);
	while (!is_some_dead(info))
	{
		i = -1;
		while (++i < info->num_philos && !is_some_dead(info))
		{
			if (get_time_since_last_eat(info, i) > info->tt_die)
				set_dead(info, i);
		}
		usleep(100);
		if (!is_some_dead(info) && eat_all(info))
		{
			printf("All philosophers have eaten!!!\n");
			set_life(info, 1, 0);
		}
	}
	return (NULL);
}

int	is_some_dead(t_info *info)
{
	int	state;

	pthread_mutex_lock(&(info)->mutex_state);
	state = info->is_some_dead;
	pthread_mutex_unlock(&(info)->mutex_state);
	return (state);
}

int	is_dead(t_info *info, int id)
{
	int	state;

	pthread_mutex_lock(&(info)->mutex_is_dead[id]);
	state = info->philo->is_dead;
	pthread_mutex_unlock(&(info)->mutex_is_dead[id]);
	return (state);
}

long	get_time_since_last_eat(t_info *info, int i)
{
	long	time_since_last_eat;

	pthread_mutex_lock(&info->mutex_last_eat[i]);
	time_since_last_eat = (calc_time() - info->time_start)
		- info->philo[i].last_eat;
	pthread_mutex_unlock(&info->mutex_last_eat[i]);
	return (time_since_last_eat);
}

void	set_dead(t_info *info, int i)
{
	set_life(info, 1, i);
	pthread_mutex_lock(&info->mutex_msg);
	printf("[%03ld] [%d] died\n", calc_time() - info->time_start, i + 1);
	pthread_mutex_unlock(&info->mutex_msg);
	if (info->num_philos == 1)
		pthread_mutex_unlock(&info->mutex_fork[0]);
}
