/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pjilo_utils_init_mutex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:59 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/11/07 17:30:50 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_mutex(t_info *info)
{
	if ((pthread_mutex_init(&info->mutex_id, NULL) != 0)
		|| (pthread_mutex_init(&info->mutex_msg, NULL) != 0)
		|| (pthread_mutex_init(&info->mutex_state, NULL) != 0)
		|| (pthread_mutex_init(&info->mutex_start, NULL) != 0)
		|| (pthread_mutex_init(&info->mutex_do_fork, NULL) != 0))
		return (1);
	if (init_mutex_last_eat(info))
		return (1);
	if (init_mutex_fork(info))
		return (1);
	if (init_mutex_is_dead(info))
		return (1);
	return (0);
}

int	init_mutex_last_eat(t_info *info)
{
	int	i;

	info->mutex_last_eat = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	if (!info->mutex_last_eat)
		return (1);
	i = 0;
	while (i < info->num_philos)
	{
		if ((pthread_mutex_init(&info->mutex_last_eat[i++], NULL) != 0))
			return (1);
	}
	return (0);
}

int	init_mutex_fork(t_info *info)
{
	int	i;

	info->mutex_fork = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	if (!info->mutex_fork)
		return (1);
	i = 0;
	while (i < info->num_philos)
	{
		if (pthread_mutex_init(&info->mutex_fork[i++], NULL) != 0)
			return (1);
	}
	return (0);
}

int	init_mutex_is_dead(t_info *info)
{
	int	i;

	info->mutex_is_dead = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	if (!info->mutex_is_dead)
		return (1);
	i = 0;
	while (i < info->num_philos)
	{
		if (pthread_mutex_init(&info->mutex_is_dead[i++], NULL) != 0)
			return (1);
	}
	return (0);
}
