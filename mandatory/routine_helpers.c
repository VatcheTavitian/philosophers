/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:45:46 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/10 12:51:29 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	go_to_sleep(useconds_t time)
{
	u_int64_t	start;

	start = timeofday();
	while ((timeofday() - start) < time)
		usleep(time / 10);
	return (0);
}

static	void	release_forks_and_sleep(t_phil *phil)
{
	pthread_mutex_unlock(phil->rfork);
	pthread_mutex_unlock(phil->lfork);
	if (!get_deathstatus(phil)
		&& (get_count(phil) < get_mineat(phil) || get_mineat(phil) == -1))
		msg("is sleeping", phil);
	go_to_sleep(phil->info->sleep_t);
}

static	void	grab_and_lock_forks(t_phil *phil)
{
	if (phil->info->total >= 2 && !(get_stop_all(phil)))
	{
		pthread_mutex_lock(phil->rfork);
		msg("has taken a fork", phil);
		pthread_mutex_lock(phil->lfork);
		msg("has taken a fork", phil);
	}
	else if (!(get_stop_all(phil)))
	{
		pthread_mutex_lock(phil->rfork);
		msg("has taken a fork", phil);
		pthread_mutex_unlock(phil->rfork);
		go_to_sleep(1000);
	}
}

void	do_eat(t_phil *phil)
{
	static int	launch;

	launch = 0;
	if (phil->id % 2 == 0 && !launch)
	{
		usleep(200);
		launch = 1;
	}
	if (get_stop_all(phil))
		return ;
	grab_and_lock_forks(phil);
	pthread_mutex_lock(&(phil->lockphil));
	phil->eating = 1;
	phil->timetodie = timeofday() + phil->info->die_t;
	msg("is eating", phil);
	phil->count++;
	go_to_sleep(phil->info->eat_t);
	phil->eating = 0;
	if (phil->count == phil->info->mineat)
		phil->status = 1;
	pthread_mutex_unlock(&(phil->lockphil));
	release_forks_and_sleep(phil);
}

int	single_philo(void *info_ptr)
{
	t_info	*info;

	info = (t_info *)info_ptr;
	info->start_t = timeofday();
	if (pthread_create(&(info->thid[0]), NULL, &routine, &(info->phil[0])) != 0)
		return (printf("Error\nFailed to create single philo thread\n"));
	if (pthread_join(info->thid[0], NULL) != 0)
		return (printf("Error\nFailed to join single philo thread\n"));
	return (0);
}
