/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:20:50 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/12 09:48:41 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

long long	time_count(void)
{
	struct timeval	time;
	int				t;

	t = gettimeofday(&time, NULL);
	if (t != 0)
	{
		write(2, "gettimeofday failed\n", 20);
		return (0);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check(t_loop *lst)
{
	if (pthread_mutex_lock(&lst->info->die) != 0)
		return (1);
	if (pthread_mutex_lock(&lst->info->mut) != 0)
		return (1);
	if (lst->info->died == 1 || lst->has_eaten == lst->info->philo_must_eat)
	{
		pthread_mutex_unlock(&lst->info->mut);
		pthread_mutex_unlock(&lst->info->die);
		return (1);
	}
	if (pthread_mutex_unlock(&lst->info->mut) != 0)
		return (1);
	if (pthread_mutex_unlock(&lst->info->die) != 0)
		return (1);
	return (0);
}

int	update(t_loop *lst, int l)
{
	if (l == 1)
	{
		if (pthread_mutex_lock(&lst->info->last_eat) != 0)
			return (1);
		lst->last_eaten = time_count();
		if (pthread_mutex_unlock(&lst->info->last_eat) != 0)
			return (1);
	}
	else
	{
		if (pthread_mutex_lock(&lst->info->mut) != 0)
			return (1);
		lst->has_eaten++;
		if (pthread_mutex_unlock(&lst->info->mut) != 0)
			return (1);
	}
	return (0);
}

int	eat(t_loop *lst)
{
	if (check(lst) == 1)
		return (-1);
	if (pthread_mutex_lock(&lst->fork) != 0)
		return (1);
	printing("has taken a fork", lst, lst->info->start_time);
	if (pthread_mutex_lock(&lst->next->fork) != 0)
		return (1);
	printing("has taken a fork", lst, lst->info->start_time);
	printing("is eating", lst, lst->info->start_time);
	if (update(lst, 1) == 1)
		return (1);
	if (ft_usleep(lst->info->eat_time, lst) == 1)
	{
		pthread_mutex_unlock(&lst->fork);
		pthread_mutex_unlock(&lst->next->fork);
		return (-1);
	}
	if (update(lst, 2) == 1)
		return (1);
	if (pthread_mutex_unlock(&lst->fork) == 0
		&& pthread_mutex_unlock(&lst->next->fork) == 0)
		return (0);
	return (1);
}

void	*life(void *arg)
{
	struct t_loop	*lst;

	lst = (struct t_loop *)arg;
	if (lst->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (check(lst) == 1)
			break ;
		if (eat(lst) != 0)
			break ;
		if (check(lst) == 1)
			break ;
		printing("is sleeping", lst, lst->info->start_time);
		if (ft_usleep(lst->info->sleep_time, lst) == 1)
			break ;
		if (check(lst) == 1)
			break ;
		printing("is thinking", lst, lst->info->start_time);
	}
	return (NULL);
}
