/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:00:11 by nsidqi            #+#    #+#             */
/*   Updated: 2024/10/18 15:09:38 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	count(char const *s, char c)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			r++;
		while (s[i] != c && s[i])
			i++;
	}
	return (r);
}

static int	ft_word(char const *s, char c)
{
	int	word;
	int	i;

	i = 0 ;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			word++;
			i++;
		}
		if (s[i - 1] != c)
			return (word);
	}
	return (0);
}

static char	**ft_free(char **res)
{
	int	i;

	i = 0;
	if (res)
	{
		while (res[i])
		{
			free(res[i]);
			i++;
		}
		free(res);
	}
	return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	size;

	i = 0;
	if (!s)
		return (0);
	size = ft_strlen(s);
	if (len > size - start)
		len = size - start;
	if (start > size)
		len = 0;
	res = malloc((len + 1) * sizeof(char));
	if (res == 0)
		return (0);
	while (i < len)
	{
		res[i] = s[start];
		start++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		j;

	j = 0;
	if (s == 0)
		return (NULL);
	res = malloc((count(s, c) + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			res[j] = ft_substr(s, 0, ft_word(s, c));
			if (!res[j])
				return (ft_free(res));
			s += ft_word(s, c);
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}
