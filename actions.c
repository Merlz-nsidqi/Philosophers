/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:20:50 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/03 16:19:44 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	eat(t_loop *lst)
{
	pthread_mutex_lock(&lst->info->mut);
	if (lst->info->died == 1)
	{
		pthread_mutex_unlock(&lst->info->mut);
		return (-1);
	}
	pthread_mutex_unlock(&lst->info->mut);
	pthread_mutex_lock(&lst->fork);
	printing("has taken a fork", lst, lst->info->start_time);
	pthread_mutex_lock(&lst->next->fork);
	printing("has taken a fork", lst, lst->info->start_time);
	printing("is eating", lst, lst->info->start_time);
	pthread_mutex_lock(&lst->info->mut);
	lst->last_eaten = time_count();
	lst->has_eaten++;
	pthread_mutex_unlock(&lst->info->mut);
	if (ft_usleep(lst->info->eat_time, lst) == 1)
	{
		pthread_mutex_unlock(&lst->fork);
		pthread_mutex_unlock(&lst->next->fork);
		return (-1);
	}
	pthread_mutex_unlock(&lst->fork);
	pthread_mutex_unlock(&lst->next->fork);
	return (0);
}

int	nor(t_loop *lst)
{
	pthread_mutex_lock(&lst->info->mut);
	if (lst->info->died == 1)
	{
		pthread_mutex_unlock(&lst->info->mut);
		return (1);
	}
	pthread_mutex_unlock(&lst->info->mut);
	return (0);
}

void	*life(void *arg)
{
	struct t_loop	*lst;

	lst = (struct t_loop *)arg;
	if (lst->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&lst->info->mut);
		if (lst->info->died == 1 || lst->has_eaten == lst->info->philo_must_eat)
		{
			pthread_mutex_unlock(&lst->info->mut);
			break ;
		}
		pthread_mutex_unlock(&lst->info->mut);
		eat(lst);
		if (nor(lst) == 1)
			break ;
		printing("is sleeping", lst, lst->info->start_time);
		if (ft_usleep(lst->info->sleep_time, lst) == 1)
			break ;
		if (nor(lst) == 1)
			break ;
		printing("is thinking", lst, lst->info->start_time);
	}
	return (NULL);
}
