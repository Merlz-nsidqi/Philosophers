/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:20:50 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/06 15:48:58 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			if ((s1[i] - s2[i]) > 0)
				return (1);
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

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

int	nor(t_loop *lst)
{
	if (pthread_mutex_lock(&lst->info->mut) != 0)
		return (1);
	if (lst->info->died == 1 || lst->has_eaten == lst->info->philo_must_eat)
	{
		pthread_mutex_unlock(&lst->info->mut);
		return (1);
	}
	if (pthread_mutex_unlock(&lst->info->mut) != 0)
		return (1);
	return (0);
}

int	eat(t_loop *lst)
{
	if (nor(lst) == 1)
		return (-1);
	if (pthread_mutex_lock(&lst->fork) != 0)
		return (1);
	printing("has taken a fork", lst, lst->info->start_time);
	if (pthread_mutex_lock(&lst->next->fork) != 0)
		return (1);
	printing("has taken a fork", lst, lst->info->start_time);
	printing("is eating", lst, lst->info->start_time);
	if (pthread_mutex_lock(&lst->info->mut) != 0)
		return (1);
	lst->last_eaten = time_count();
	lst->has_eaten++;
	if (pthread_mutex_unlock(&lst->info->mut) != 0)
		return (1);
	if (ft_usleep(lst->info->eat_time, lst) == 1)
	{
		pthread_mutex_unlock(&lst->fork);
		pthread_mutex_unlock(&lst->next->fork);
		return (-1);
	}
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
		if (nor(lst) == 1)
			break ;
		if (eat(lst) != 0)
			break ;
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
