/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:59 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/11/07 17:26:24 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_info(t_info *info)
{
	int	i;

	i = -1;
	info->id = 0;
	info->is_some_dead = 0;
	info->philo = malloc(sizeof(t_philo) * info->num_philos);
	info->fork_used = malloc(sizeof(t_philo) * info->num_philos);
	if (!info->philo || !info->fork_used)
		return (1);
	while (++i < info->num_philos)
		info->fork_used[i] = 0;
	i = -1;
	return (0);
}

int	create_thread(t_info *info)
{
	int	i;

	info->thread = malloc(sizeof(pthread_t) * info->num_philos);
	if (!info->thread)
		return (1);
	pthread_mutex_lock(&info->mutex_start);
	i = 0;
	while (i < info->num_philos)
	{
		if (pthread_create(&info->thread[i], NULL,
				&rutine, (void *) info) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&info->thread_is_dead, NULL,
			&is_alive, (void *) info) != 0)
		return (1);
	info->time_start = calc_time();
	i = 0;
	pthread_mutex_unlock(&info->mutex_start);
	return (0);
}
