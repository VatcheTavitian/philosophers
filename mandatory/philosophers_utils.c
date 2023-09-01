/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:49:14 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/10 12:49:53 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	msg(char *str, t_phil *phil)
{
	if (ft_strncmp("has died!", str, 9) == 0
		&& get_deathstatus(phil) == 0)
	{
		if (get_deathstatus(phil))
			return ;
		pthread_mutex_lock(&(phil->info->death_m));
		phil->info->death = 1;
		phil->info->stop_all = 1;
		pthread_mutex_unlock(&(phil->info->death_m));
		pthread_mutex_unlock(phil->rfork);
		pthread_mutex_unlock(phil->lfork);
		pthread_mutex_lock(&(phil->info->mutex));
		printf("%d Philosopher %d %s\n", get_time(phil), phil->id, str);
		pthread_mutex_unlock(&(phil->info->mutex));
	}
	else
	{
		if (get_deathstatus(phil) || get_stop_all(phil))
			return ;
		pthread_mutex_lock(&(phil->info->mutex));
		if (!(get_deathstatus(phil)))
			printf("%d Philosopher %d %s\n", get_time(phil), phil->id, str);
		pthread_mutex_unlock(&(phil->info->mutex));
	}
}

uint64_t	timeofday(void)
{
	struct timeval	timeval;
	uint64_t		time;

	gettimeofday(&timeval, NULL);
	time = (timeval.tv_sec * (u_int64_t)1000) + (timeval.tv_usec / 1000);
	return ((timeval.tv_sec * (u_int64_t)1000) + (timeval.tv_usec / 1000));
}

static int	check_nums_only(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argc-- >= 2)
	{
		while (argv[i][j] != '\0')
		{
			if (!(ft_isdigit(argv[i][j])))
				return (-1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	checkerrors(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (-1);
	if (check_nums_only(argc, argv) == -1)
		return (-1);
	while (i < argc)
	{
		if (!(ft_atoi(argv[i])) || ft_atoi(argv[i]) <= 0)
			return (-1);
		i++;
	}
	return (0);
}
