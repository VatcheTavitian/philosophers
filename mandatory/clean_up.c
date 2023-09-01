/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:53:40 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/07 19:08:00 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_time(void *phil)
{
	int		time;
	t_phil	*phil_ptr;

	phil_ptr = (t_phil *)phil;
	time = 0;
	pthread_mutex_lock(&(phil_ptr->info->update));
	time = timeofday() - phil_ptr->info->start_t;
	pthread_mutex_unlock(&(phil_ptr->info->update));
	return (time);
}

static void	clear_data(t_info *data)
{
	if (data->thid)
		free(data->thid);
	if (data->forks)
		free(data->forks);
	if (data->phil)
		free(data->phil);
}

void	clean_up(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->total)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->phil[i].lockphil);
		i++;
	}
	pthread_mutex_destroy(&data->update);
	pthread_mutex_destroy(&data->mutex);
	clear_data(data);
}
