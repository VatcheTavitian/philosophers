/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:48:04 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/10 13:20:34 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	initialise_phils(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->total)
	{
		info->phil[i].info = info;
		info->phil[i].id = i + 1;
		info->phil[i].count = 0;
		info->phil[i].status = 0;
		info->phil[i].eating = 0;
		info->phil[i].timetodie = info->die_t;
		pthread_mutex_init(&(info->phil[i].lockphil), NULL);
		i++;
	}
}

static void	initialise_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->total)
	{
		pthread_mutex_init(&(info->forks[i]), NULL);
		i++;
	}
	info->phil[0].lfork = &info->forks[0];
	info->phil[0].rfork = &info->forks[info->total - 1];
	i = 1;
	while (i < info->total)
	{
		info->phil[i].lfork = &info->forks[i];
		info->phil[i].rfork = &info->forks[i - 1];
		i++;
	}
}

static int	info_helper(t_info	*info)
{
	int	tl;

	tl = info->total;
	info->thid = (pthread_t *)malloc(sizeof(pthread_t) * tl);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * tl);
	info->phil = (t_phil *)malloc(sizeof(t_phil) * tl);
	if (!(info->phil || info->thid || info->forks))
		return (printf("Error\nUnable to allocate memory to info struct...\n"));
	return (0);
}

static void	initialise_info(t_info *info, int argc, char **argv)
{
	info->death = 0;
	info->stop_all = 0;
	info->finished = 0;
	info->total = ft_atoi(argv[1]);
	info->die_t = (suseconds_t)ft_atoi(argv[2]);
	info->eat_t = (suseconds_t)ft_atoi(argv[3]);
	info->sleep_t = (suseconds_t)ft_atoi(argv[4]);
	if (argc == 6)
		info->mineat = ft_atoi(argv[5]);
	else
		info->mineat = -1;
	pthread_mutex_init(&(info->mutex), NULL);
	pthread_mutex_init(&(info->update), NULL);
	pthread_mutex_init(&(info->death_m), NULL);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		forks;

	if (checkerrors(argc, argv) == -1)
		return (printf("Error\nCheck input arguments are valid\n"));
	initialise_info(&info, argc, argv);
	info_helper(&info);
	initialise_forks(&info);
	initialise_phils(&info);
	if (ft_atoi(argv[1]) == 1)
		single_philo(&info);
	else
		execute_all(&info);
	clean_up(&info);
	return (0);
}
