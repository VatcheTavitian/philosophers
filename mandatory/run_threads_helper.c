/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_threads_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:54:42 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/10 11:25:50 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_status(void *phil)
{
	int		status;
	t_phil	*phil_ptr;

	phil_ptr = (t_phil *)phil;
	status = 0;
	pthread_mutex_lock(&(phil_ptr->lockphil));
	status = phil_ptr->status;
	pthread_mutex_unlock(&(phil_ptr->lockphil));
	return (status);
}

int	get_stop_all(void *phil)
{
	int		stop_all;
	t_phil	*phil_ptr;

	phil_ptr = (t_phil *)phil;
	pthread_mutex_lock(&(phil_ptr->info->death_m));
	stop_all = phil_ptr->info->stop_all;
	pthread_mutex_unlock(&(phil_ptr->info->death_m));
	return (stop_all);
}

int	get_count(void *phil)
{
	int		count;
	t_phil	*phil_ptr;

	phil_ptr = (t_phil *)phil;
	count = 0;
	pthread_mutex_lock(&(phil_ptr->lockphil));
	count = phil_ptr->count;
	pthread_mutex_unlock(&(phil_ptr->lockphil));
	return (count);
}

int	get_mineat(void *phil)
{
	int		mineat;
	t_phil	*phil_ptr;

	phil_ptr = (t_phil *)phil;
	mineat = 0;
	pthread_mutex_lock(&(phil_ptr->lockphil));
	mineat = phil_ptr->info->mineat;
	pthread_mutex_unlock(&(phil_ptr->lockphil));
	return (mineat);
}

int	get_deathstatus(void *phil)
{
	int		deathstatus;
	t_phil	*phil_ptr;

	phil_ptr = (t_phil *)phil;
	deathstatus = 0;
	pthread_mutex_lock(&(phil_ptr->info->death_m));
	deathstatus = phil_ptr->info->death;
	pthread_mutex_unlock(&(phil_ptr->info->death_m));
	return (deathstatus);
}
