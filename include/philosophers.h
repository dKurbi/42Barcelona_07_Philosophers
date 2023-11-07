/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:01:55 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/11/07 17:55:54 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				num_eats;
	long			last_eat;
	int				is_dead;
}	t_philo;

typedef struct s_info
{
	int				init_philo;
	int				is_some_dead;
	int				id;
	int				num_philos;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				time_think;
	int				num_phil_must_eat;
	int				*fork_used;
	t_philo			*philo;
	pthread_t		*thread;	
	pthread_t		thread_is_dead;
	pthread_t		thread_print;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*mutex_last_eat;
	pthread_mutex_t	*mutex_is_dead;	
	pthread_mutex_t	mutex_msg;
	pthread_mutex_t	mutex_state;
	pthread_mutex_t	mutex_start;
	pthread_mutex_t	mutex_id;
	pthread_mutex_t	mutex_do_fork;
	long			time_start;
}	t_info;

//		Utils_rutine
void	*rutine(void *arg);
int		eat_all(t_info *info);
void	set_last_eat(t_info *info, int id, int first);

//		Utils_actions
void	go_to_sleep(t_info *info, int id);
void	go_to_think(t_info *info, int id);
void	take_a_fork(t_info *info, int id);
int		both_fork_are_free(t_info *info, int id);
void	eat(t_info *info, int id);

//		Utils_ft_atoi
int		ft_atoi(const char *str);

//		Utils_init
int		init_info(t_info *info);
int		create_thread(t_info *info);

//		Utils_init_mutex
int		init_mutex(t_info *info);
int		init_mutex_last_eat(t_info *info);
int		init_mutex_fork(t_info *info);
int		init_mutex_is_dead(t_info *info);

//		Utils_others
long	calc_time(void);
void	print_message(char *str, t_info *info, int id);
void	set_life(t_info *info, int is_dead, int id);
void	to_wait(long time);
void	to_wait_to_eat(long time);

//		Utils_check_dead
void	*is_alive(void *arg);
int		is_some_dead(t_info *info);
int		is_dead(t_info *info, int id);
long	get_time_since_last_eat(t_info *info, int i);
void	set_dead(t_info *info, int i);

//		Utils_free
void	mutex_destroy(t_info *info);
void	free_all(t_info *info);
int		join_tread(t_info *info);

#endif
