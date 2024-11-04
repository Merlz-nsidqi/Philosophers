/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:57:17 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/04 16:40:31 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <libc.h>
# include <pthread.h>

typedef struct t_info
{
	int				philo_num;
	long long		start_time;
	long long		death_time;
	long long		eat_time;
	long long		sleep_time;
	long long		philo_must_eat;
	int				died;
	pthread_t		monit;
	pthread_mutex_t	mut;
}	t_info;

typedef struct t_loop
{
	t_info			*info;
	int				id;
	int				has_eaten;
	long long		last_eaten;
	pthread_mutex_t	fork;
	pthread_t		thread;
	struct t_loop	*next;
}	t_loop;

//fts funcs:
char		**ft_split(char *s, char c);
int			ft_strlen(char *s);
long long	ft_atoi(const char *str);
char		*ft_strchr(const char *s, int c);
//parsing funcs:
int			list_put(t_info **inf, int *c, char *r);
int			parse(char **av, int *c, t_info **inf, int j);
int			parse2(t_info **inf, char *av, int *c);
t_loop		*new(t_info **inf, int i);
//philo funcs:
void		run(t_info **inf, t_loop **p);
int			eat(t_loop *lst);
void		*life(void *arg);
long long	time_count(void);
int			ft_usleep(size_t milliseconds, t_loop *lst);
void		*monitor(void *arg);
void		printing(char *msg, t_loop *lst, long long m);

#endif
