/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:07:38 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/09 12:40:18 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	mutex_init(t_loop **p, t_info **inf)
{
	int	t;

	if (pthread_mutex_init(&(*inf)->mut, NULL) != 0)
		return (freeing(inf, p), 1);
	if (pthread_mutex_init(&(*inf)->die, NULL) != 0)
		return (freeing(inf, p), 1);
	if (pthread_mutex_init(&(*inf)->last_eat, NULL) != 0)
		return (freeing(inf, p), 1);
	if (pthread_mutex_init(&(*inf)->print, NULL) != 0)
		return (freeing(inf, p), 1);
	t = (*inf)->philo_num;
	while (t > 0)
	{
		if (pthread_mutex_init(&(*p)->fork, NULL) != 0)
			return (freeing(inf, p), 1);
		*p = (*p)->next;
		t--;
	}
	return (0);
}
