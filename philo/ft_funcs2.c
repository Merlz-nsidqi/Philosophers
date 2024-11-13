/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_funcs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:34:37 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/13 08:21:38 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long long	ft_handle(const char *str, int sign, int i)
{
	long long	nb;
	long long	n;

	n = 0;
	nb = 0;
	while (str[i])
	{
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		if (str[i] == '\0')
			return (nb * sign);
		if (str[i] >= '0' && str[i] <= '9')
		{
			n = (nb * 10) + (str[i] - '0');
			if (n < nb && sign == 1)
				return (-1);
			else if (n < nb && sign == -1)
				return (0);
			nb = n;
		}
		else
			return (write(2, "numeric args required\n", 22), -1);
		i++;
	}
	return (nb * sign);
}

long long	ft_atoi(const char *str)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (write(2, "positive args required\n", 23), -1);
		i++;
	}
	if (str[i] == '\0')
		return (write(2, "numeric args required\n", 22), -1);
	return (ft_handle(str, sign, i));
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (0);
}

int	ft_usleep(size_t milliseconds, t_loop *lst)
{
	size_t	start;

	start = time_count();
	while ((time_count() - start) < milliseconds)
	{
		if (pthread_mutex_lock(&lst->info->die) != 0)
			return (1);
		if (lst->info->died == 1)
		{
			pthread_mutex_unlock(&lst->info->die);
			return (1);
		}
		if (pthread_mutex_unlock(&lst->info->die) != 0)
			return (1);
		usleep(100);
	}
	return (0);
}
