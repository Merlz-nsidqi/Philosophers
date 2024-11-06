/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   added.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:05:01 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/06 15:49:14 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	freer(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

int	parse2(t_info **inf, char *av, int *c)
{
	char	**res;
	int		i;
	int		g;

	i = 0;
	res = NULL;
	if (ft_strchr(av, ' ') != NULL)
		res = ft_split(av, ' ');
	else if (ft_strchr(av, '\t') != NULL)
		res = ft_split(av, '\t');
	while (res[i])
	{
		g = list_put(inf, c, res[i]);
		if (g == 1)
			return (freer(res), 1);
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}

t_loop	*new(t_info **inf, int i)
{
	t_loop	*new;

	new = malloc(sizeof(t_loop));
	if (!new)
		return (NULL);
	new->id = i;
	new->info = *inf;
	new->last_eaten = (*inf)->start_time;
	return (new);
}

void	printing(char *msg, t_loop *lst, long long m)
{
	long long	time;

	if (pthread_mutex_lock(&lst->info->mut) != 0)
		return ;
	if (lst->info->died == 0)
	{
		time = time_count();
		printf("%lld  %d %s\n", time - m, lst->id, msg);
	}
	if (pthread_mutex_unlock(&lst->info->mut) != 0)
		return ;
	if (ft_strcmp(msg, "died") == 0)
	{
		if (pthread_mutex_lock(&lst->info->mut) != 0)
			return ;
		lst->info->died = 1;
		if (pthread_mutex_unlock(&lst->info->mut) != 0)
			return ;
	}
}
