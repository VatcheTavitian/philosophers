/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:50:06 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/10 12:52:07 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*supervisor(void *phil)
{
	t_phil	*phil_ptr;

	phil_ptr = (t_phil *)phil;
	while (get_deathstatus(phil) == 0)
	{	
		pthread_mutex_lock(&(phil_ptr->lockphil));
		if (phil_ptr->count == phil_ptr->info->mineat)
		{	
			pthread_mutex_lock(&(phil_ptr->info->update));
			phil_ptr->info->finished += 1;
			phil_ptr->count += 1;
			pthread_mutex_unlock(&(phil_ptr->info->update));
		}
		if (timeofday() >= phil_ptr->timetodie && phil_ptr->eating == 0)
			msg("has died!", phil_ptr);
		if (get_stop_all(phil) || get_deathstatus(phil))
		{
			pthread_mutex_unlock(&(phil_ptr->lockphil));
			break ;
		}
		pthread_mutex_unlock(&(phil_ptr->lockphil));
	}
	return ((void *) 0);
}

void	*routine(void *phil)
{
	t_phil	*phil_ptr;

	phil_ptr = (t_phil *)phil;
	phil_ptr->timetodie = phil_ptr->info->die_t + timeofday();
	if (pthread_create(&phil_ptr->th_phils, NULL, &supervisor, (void *)phil_ptr)
		!= 0)
		return ((void *) -1);
	while (get_deathstatus(phil) == 0 && get_stop_all(phil) == 0
		&& (get_count(phil) < get_mineat(phil) || get_mineat(phil) == -1)
		&& (!get_status(phil)))
	{
		do_eat(phil_ptr);
		if (!get_deathstatus(phil)
			&& (get_count(phil) < get_mineat(phil) || get_mineat(phil) == -1))
			msg("is thinking", phil_ptr);
	}
	if (pthread_join(phil_ptr->th_phils, NULL))
		return ((void *) -1);
	return ((void *) 0);
}

void	*check_func(void *phil)
{
	t_phil	*phil_ptr;

	phil_ptr = (t_phil *)phil;
	while (get_deathstatus(phil) == 0 && get_stop_all(phil) == 0)
	{
		pthread_mutex_lock(&(phil_ptr->lockphil));
		pthread_mutex_lock(&(phil_ptr->info->update));
		if (phil_ptr->info->finished >= phil_ptr->info->total)
		{
			pthread_mutex_lock(&(phil_ptr->info->death_m));
			phil_ptr->info->stop_all = 1;
			pthread_mutex_unlock(&(phil_ptr->info->death_m));
		}
		pthread_mutex_unlock(&(phil_ptr->lockphil));
		pthread_mutex_unlock(&(phil_ptr->info->update));
	}
	return ((void *)0);
}

static int	create_threads(t_info *info)
{
	int			i;
	t_phil		*phil;

	i = 0;
	phil = info->phil;
	while (i < info->total)
	{
		if (i % 2 == 0)
		{
			usleep(2500);
			if (pthread_create(&(info->thid[i]), NULL, &routine, &(phil[i])))
				return (printf("Error\nFailed to create routine threads\n"));
		}
		else
		{
			if (pthread_create(&(info->thid[i]), NULL, &routine, &(phil[i])))
				return (printf("Error\nFailed to create routine threads\n"));
		}
		i++;
	}
	return (0);
}

int	execute_all(t_info *info)
{
	int			i;
	pthread_t	checker;

	i = 0;
	info->start_t = timeofday();
	if (info->mineat > 0)
	{
		if (pthread_create(&checker, NULL, &check_func, &(info->phil[0])) != 0)
			return (printf("Error\nFailed to create checker threads\n"));
	}
	create_threads(info);
	while (i < info->total)
	{
		if (pthread_join(info->thid[i], NULL) != 0)
			return (printf("Error\nFailed to join threads\n"));
		i++;
	}
	if (info->mineat > 0)
	{
		if (pthread_join(checker, NULL) != 0)
			return (printf("Error\nFailed to join checker thread\n"));
	}
	return (0);
}
