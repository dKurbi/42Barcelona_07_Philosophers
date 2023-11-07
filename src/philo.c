/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:53:18 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/11/07 17:51:36 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	error_arguments(char i)
{
	if (i == 0)
		write(1, "Invalid number of arguments.\n", 29);
	else
		write(1, "Arguments error.\n", 17);
	printf("./philo [n_of_philo] [tt_die] [tt_eat] [tt_sleep] ");
	printf("optional : [number_of_times_each_philosopher_must_eat]\n" );
}

static int	check_num_arg(char *num_arg, int pos, t_info *info)
{
	int	n;

	n = ft_atoi(num_arg);
	if (!n || n < 0 || (pos == 1 && n > 200) || (pos == 2 && n < 60)
		|| (pos == 3 && n < 60) || (pos == 4 && n < 60))
	{
		free(info);
		error_arguments(1);
		return (-1);
	}
	else
	{
		if (pos == 1)
			info->num_philos = n;
		if (pos == 2)
			info->tt_die = n;
		if (pos == 3)
			info->tt_eat = n;
		if (pos == 4)
			info->tt_sleep = n;
		if (pos == 5)
			info->num_phil_must_eat = n;
		return (n);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_info	*info;

	if (argc != 5 && argc != 6)
	{
		error_arguments(0);
		return (0);
	}
	i = 1;
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	while (i != argc)
	{
		if (check_num_arg(argv[i], i, info) < 0)
			return (0);
		i++;
	}
	if (argc == 5)
		info->num_phil_must_eat = -1;
	init_info(info);
	init_mutex(info);
	create_thread(info);
	join_tread(info);
	free_all(info);
}
