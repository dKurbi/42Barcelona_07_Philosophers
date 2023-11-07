/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_rutine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:13:05 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/11/07 17:45:10 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*rutine(void *arg)
{
	int		i;
	t_info	*info;

	info = (t_info *) arg;
	pthread_mutex_lock(&info->mutex_id);
	i = info->id;
	set_life(info, 0, i);
	info->philo[i].num_eats = info->num_phil_must_eat;
	info->id++;
	pthread_mutex_unlock(&info->mutex_id);
	pthread_mutex_lock(&info->mutex_start);
	set_last_eat(info, i, 1);
	pthread_mutex_unlock(&info->mutex_start);
	if (i % 2 == 1)
		to_wait(info->tt_eat);
	while (!is_some_dead(info))
	{
		take_a_fork(info, i);
		eat(info, i);
		go_to_sleep(info, i);
		go_to_think(info, i);
	}
	return (NULL);
}

int	eat_all(t_info *info)
{
	int	i;
	int	need_to_eat;

	i = -1;
	need_to_eat = 0;
	if (info->num_phil_must_eat != -1)
	{
		while (++i < info->num_philos)
		{
			pthread_mutex_lock(&info->mutex_last_eat[i]);
			need_to_eat += info->philo[i].num_eats;
			pthread_mutex_unlock(&info->mutex_last_eat[i]);
		}
		if (need_to_eat == 0)
			return (1);
	}
	return (0);
}

void	set_last_eat(t_info *info, int id, int first)
{
	pthread_mutex_lock(&info->mutex_last_eat[id]);
	info->philo[id].last_eat = calc_time() - info->time_start;
	if (!first)
	{
		if (info->philo[id].num_eats > 0)
			info->philo[id].num_eats--;
	}
	pthread_mutex_unlock(&info->mutex_last_eat[id]);
}
