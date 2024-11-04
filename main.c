/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:24:32 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/04 16:40:27 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	create_circular_list(t_loop **p, int philo_num, t_info **inf, int i)
{
	t_loop		*head;
	t_loop		*current;
	t_loop		*new_node;

	head = NULL;
	current = NULL;
	while (philo_num > 0)
	{
		new_node = new(inf, i);
		if (new_node == NULL)
			return (1);
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
		philo_num--;
	}
	if (current != NULL)
		current->next = head;
	*p = head;
	return (0);
}

int	start(int ac, char **av, t_info **inf, t_loop **p)
{
	int	c;

	c = 0;
	if (ac > 6 || ac <= 1)
		return (write(2, "wrong arguments\n", 16), 1);
	if (parse(av, &c, inf, 1) == 1)
		return (1);
	if (c > 5 || c < 4)
		return (write(2, "wrong arguments\n", 16), 1);
	if ((*inf)->philo_num == 0)
		return (write(2, "There's no philo's!!\n", 22), 1);
	if ((*inf)->philo_num < 0)
		return (write(2, "Philo's can't be negative\n", 26), 1);
	if ((*inf)->philo_num > 200)
		return (write(2, "too many philo's\n", 17), 1);
	if ((*inf)->death_time < 60 || (*inf)->sleep_time < 60
		|| (*inf)->eat_time < 60)
		return (write(2, "Can't be less than 60\n", 22), 1);
	(*inf)->died = 0;
	(*inf)->start_time = time_count();
	return (create_circular_list(p, (*inf)->philo_num, inf, 1));
}

void	one_philo(t_info **inf, t_loop **p)
{
	long long	t;

	t = time_count();
	printf("%lld  %d has taken a fork\n", t - (*inf)->start_time, (*p)->id);
	t = time_count();
	ft_usleep((*inf)->eat_time, *p);
	printf("%lld  %d died\n", t - (*inf)->start_time, (*p)->id);
}

void	freeing(t_info **inf, t_loop **p)
{
	int	t;

	if (*inf != NULL)
		free(*inf);
	if (*inf == NULL || *p == NULL)
		return ;
	t = (*inf)->philo_num;
	pthread_mutex_destroy(&(*inf)->mut);
	while (t > 0)
	{
		pthread_mutex_destroy(&(*p)->fork);
		free(*p);
		*p = (*p)->next;
		t--;
	}
}

int	main(int ac, char **av)
{
	t_info	*inf;
	t_loop	*p;

	if (start(ac, av, &inf, &p) == 0)
	{
		pthread_mutex_init(&inf->mut, NULL);
		if (inf->philo_num == 1)
			one_philo(&inf, &p);
		else
			run(&inf, &p);
	}
	freeing(&inf, &p);
	return (0);
}
