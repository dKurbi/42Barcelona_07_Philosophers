/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:10:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/11/07 18:08:53 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	mutex_destroy(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info->mutex_id);
	pthread_mutex_destroy(&info->mutex_msg);
	pthread_mutex_destroy(&info->mutex_do_fork);
	pthread_mutex_destroy(&info->mutex_state);
	pthread_mutex_destroy(&info->mutex_start);
	while (i < info->num_philos)
		pthread_mutex_destroy(&info->mutex_fork[i++]);
	i = 0;
	while (i < info->num_philos)
		pthread_mutex_destroy(&info->mutex_last_eat[i++]);
	i = 0;
	while (i < info->num_philos)
		pthread_mutex_destroy(&info->mutex_is_dead[i++]);
	i = 0;
}

void	free_all(t_info *info)
{
	int	i;

	mutex_destroy(info);
	i = 0;
	while (i < info->num_philos)
		pthread_mutex_destroy(&info->mutex_is_dead[i++]);
	i = 0;
	while (i < info->num_philos)
		pthread_detach(info->thread[i++]);
	pthread_detach(info->thread_is_dead);
	free(info->mutex_last_eat);
	free(info->mutex_is_dead);
	free(info->mutex_fork);
	free(info->thread);
	free(info->philo);
	free(info->fork_used);
	free(info);
}

int	join_tread(t_info *info)
{
	int	i;

	i = -1;
	if (info->num_philos > 1)
	{
		while (++i < info->num_philos)
		{
			if (pthread_join(info->thread[i], NULL) != 0)
				return (1);
		}
	}
	else
	{
		if (pthread_join(*(info->thread), NULL) != 0)
			return (1);
	}
	if (pthread_join(info->thread_is_dead, NULL) != 0)
		return (1);
	return (0);
}
