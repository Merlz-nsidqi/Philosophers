/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsidqi <nsidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:57:17 by nsidqi            #+#    #+#             */
/*   Updated: 2024/11/13 08:31:42 by nsidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
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
	pthread_mutex_t	die;
	pthread_mutex_t	last_eat;
	pthread_mutex_t	print;
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
void		freeing(t_info **inf, t_loop **p);
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
int			check(t_loop *lst);
int			mutex_init(t_loop **p, t_info **inf);

#endif
