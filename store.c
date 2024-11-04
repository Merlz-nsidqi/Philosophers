/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:46:27 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/04 16:42:45 by nsidqi           ###   ########.fr       */
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

int	list_put(t_info **inf, int *c, char *r)
{
	int			i;
	long long	res;

	i = 0;
	while (r[i] == ' ' || r[i] == '\t')
		i++;
	if (r[i] == '\0')
		return (1);
	res = ft_atoi(r);
	if (res == -1)
		return (1);
	if (*c != 4)
		(*inf)->philo_must_eat = -1;
	if (*c == 0)
		(*inf)->philo_num = res;
	else if (*c == 1)
		(*inf)->death_time = res;
	else if (*c == 2)
		(*inf)->eat_time = res;
	else if (*c == 3)
		(*inf)->sleep_time = res;
	else if (*c == 4)
		(*inf)->philo_must_eat = res;
	(*c)++;
	return (0);
}

int	parse(char **av, int *c, t_info **inf, int j)
{
	int		i;
	int		g;

	*inf = malloc(sizeof(t_info));
	while (av[j])
	{
		i = 0;
		if (ft_strchr(av[j], ' ') == NULL && ft_strchr(av[j], '\t') == NULL)
		{
			if (av[j][0] == '\0')
				return (write(2, "empty arguments\n", 16), 1);
			g = list_put(inf, c, av[j]);
			if (g == 1)
				return (1);
		}
		else
		{
			if (parse2(inf, av[j], c) == 1)
				return (1);
		}
		j++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	struct t_loop	*lst;

	lst = (struct t_loop *)arg;
	while (1)
	{
		pthread_mutex_lock(&lst->info->mut);
		if (lst->info->died == 1 || lst->has_eaten == lst->info->philo_must_eat)
		{
			pthread_mutex_unlock(&lst->info->mut);
			break ;
		}
		if ((time_count() - lst->last_eaten) >= lst->info->death_time)
		{
			pthread_mutex_unlock(&lst->info->mut);
			printing("died", lst, lst->last_eaten);
			pthread_mutex_lock(&lst->info->mut);
			lst->info->died = 1;
			pthread_mutex_unlock(&lst->info->mut);
			break ;
		}
		pthread_mutex_unlock(&lst->info->mut);
		usleep(100);
		lst = lst->next;
	}
	return (NULL);
}

void	run(t_info **inf, t_loop **p)
{
	int	t;

	t = (*inf)->philo_num;
	while (t > 0)
	{
		pthread_mutex_init(&(*p)->fork, NULL);
		*p = (*p)->next;
		t--;
	}
	while (t < (*inf)->philo_num)
	{
		pthread_create(&(*p)->thread, NULL, life, *p);
		*p = (*p)->next;
		t++;
	}
	pthread_create(&(*inf)->monit, NULL, monitor, *p);
	pthread_join((*inf)->monit, NULL);
	while (t > 0)
	{
		pthread_join((*p)->thread, NULL);
		*p = (*p)->next;
		t--;
	}
}
