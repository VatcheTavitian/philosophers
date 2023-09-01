/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:37:47 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/07 17:16:58 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

struct	s_info;

typedef struct s_phil {
	struct s_info	*info;
	pthread_t		th_phils;
	int				id;
	int				count;
	int				status;
	int				eating;
	uint64_t		timetodie;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	lockphil;
}					t_phil;

typedef struct s_info {
	pthread_mutex_t	mutex;
	pthread_mutex_t	death_m;
	pthread_mutex_t	*forks;
	pthread_mutex_t	update;
	pthread_t		*thid;
	t_phil			*phil;
	int				total;
	int				mineat;
	int				death;
	int				finished;
	int				stop_all;
	uint64_t		eat_t;
	uint64_t		die_t;
	uint64_t		sleep_t;
	uint64_t		start_t;
}					t_info;

int			ft_atoi(const char *str);
int			checkerrors(int argc, char **argv);
int			ft_isdigit(int c);
int			execute_all(t_info *info);
uint64_t	timeofday(void);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		do_eat(t_phil *phil);
void		msg(char *str, t_phil *phil);
int			get_deathstatus(void *phil);
int			single_philo(void *phil);
void		ft_exit(t_info *data);
void		*routine(void *phil);
void		clean_up(t_info *data);
int			get_time(void *phil);
int			get_mineat(void *phil);
int			get_count(void *phil);
int			get_status(void *phil);
int			get_stop_all(void *phil);

#endif