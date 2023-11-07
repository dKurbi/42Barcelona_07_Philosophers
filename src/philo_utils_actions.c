/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:39:20 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/11/07 17:13:40 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	go_to_sleep(t_info *info, int id)
{
	print_message("is sleeping", info, id);
	to_wait(info->tt_sleep);
}

void	go_to_think(t_info *info, int id)
{
	print_message("is thinking", info, id);
}

void	take_a_fork(t_info *info, int id)
{
	while (!both_fork_are_free(info, id))
	{
		usleep(1);
	}
	pthread_mutex_lock(&info->mutex_fork[id]);
	info->fork_used[id] = 1;
	print_message("has taken a fork left", info, id);
	pthread_mutex_lock(&info->mutex_fork[(id + 1) % info->num_philos]);
	info->fork_used[(id + 1) % info->num_philos] = 1;
	print_message("has taken a fork right", info, id);
}

int	both_fork_are_free(t_info *info, int id)
{
	int	fork_left_is_used;
	int	fork_right_is_used;

	if (info->num_philos > 1)
	{
		pthread_mutex_lock(&info->mutex_fork[id]);
		fork_left_is_used = info->fork_used[id];
		pthread_mutex_unlock(&info->mutex_fork[id]);
		pthread_mutex_lock(&info->mutex_fork[(id + 1) % info->num_philos]);
		fork_right_is_used = info->fork_used[(id + 1) % info->num_philos];
		pthread_mutex_unlock(&info->mutex_fork[(id + 1) % info->num_philos]);
		if (!fork_left_is_used && !fork_right_is_used)
			return (1);
		else
			return (0);
	}
	return (1);
}

void	eat(t_info *info, int id)
{
	set_last_eat(info, id, 0);
	print_message("is eating", info, id);
	to_wait_to_eat(info->philo[id].last_eat + info->time_start + info->tt_eat);
	info->fork_used[id] = 0;
	info->fork_used[(id + 1) % info->num_philos] = 0;
	pthread_mutex_unlock(&info->mutex_fork[id]);
	pthread_mutex_unlock(&info->mutex_fork[(id + 1) % info->num_philos]);
}
