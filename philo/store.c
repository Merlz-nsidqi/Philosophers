/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:46:27 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/09 11:52:30 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

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
		if (check(lst) == 1)
			return (0);
		if (pthread_mutex_lock(&lst->info->last_eat) != 0)
			return (0);
		if ((time_count() - lst->last_eaten) >= lst->info->death_time)
		{
			printing("died", lst, lst->info->start_time);
			pthread_mutex_unlock(&lst->info->last_eat);
			break ;
		}
		if (pthread_mutex_unlock(&lst->info->last_eat) != 0)
			return (0);
		lst = lst->next;
	}
	return (NULL);
}

int	moni_create(t_info **inf, t_loop **p)
{
	if (pthread_create(&(*inf)->monit, NULL, monitor, *p) != 0)
	{
		write(2, "Creation of thread failed\n", 26);
		return (1);
	}
	if (pthread_join((*inf)->monit, NULL) != 0)
	{
		write(2, "Joining of thread failed\n", 25);
		return (1);
	}
	return (0);
}

void	run(t_info **inf, t_loop **p)
{
	int	t;

	t = (*inf)->philo_num;
	while (t > 0)
	{
		if (pthread_create(&(*p)->thread, NULL, life, *p) != 0)
		{
			write(2, "Creation of thread failed\n", 26);
			return ;
		}
		*p = (*p)->next;
		t--;
	}
	if (moni_create(inf, p) == 1)
		return ;
	while (t < (*inf)->philo_num)
	{
		if (pthread_join((*p)->thread, NULL) != 0)
		{
			write(2, "Joining of thread failed\n", 25);
			return ;
		}
		*p = (*p)->next;
		t++;
	}
}
