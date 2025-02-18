/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:35:00 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/21 13:09:34 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>
# include <limits.h>

# ifndef DEBUG
#  define DEBUG 1
# endif

// colors
# define RESET	"\033[0m"
# define BLACK	"\033[0;30m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define BLUE	"\033[0;34m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define WHITE	"\033[0;37m"
# define GRAY	"\033[0;30m"

// Background
# define B_BLACK	"\033[40m"
# define B_RED		"\033[41m"
# define B_GREEN	"\033[42m"
# define B_YELLOW	"\033[43m"
# define B_BLUE		"\033[44m"
# define B_PURPLE	"\033[45m"
# define B_CYAN		"\033[46m"
# define B_WHITE	"\033[47m"

typedef struct s_settings
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_time_each_philosopher_must_eat;
	int	should_stop;
}	t_settings;

typedef enum e_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
}	t_state;

typedef struct s_philosopher
{
	int			id;
	int			meal_eaten;
	long int	last_meal;
	pthread_t	thread;
	t_state		state;
}	t_philosopher;

typedef struct s_fork
{
	int				id;
	int				is_used;
	pthread_mutex_t	mutex;
}	t_fork;

// main.c
int			main(int argc, char **argv);
int			end(t_philosopher *philos, t_fork *forks);

// setup.c
void		init(t_philosopher **philos, t_fork **forks);
int			create_philos_forks(t_philosopher **philos, t_fork **forks);

// forks.c
t_fork		**get_forks(t_fork **set_forks);
int			toggle_fork(t_philosopher *philo, int reset);

// atoi.c
int			ft_atoi(const char *nptr);
int			overflow_check(const char *s, void (*f)(int, void *), void *param);

// philosophers
void		do_action(t_philosopher *philo, t_state action);
void		*philosophing(void *param_philo);

// time.c
int			get_time_left(const t_philosopher *philo);
long		get_current_time_ms(void);
int			sleep_ms(int ms);

// utils.c
void		print_state(const t_philosopher *philo, const char *msg);

// errors.c
int			check_errors(int count, char **values);

// settings.c
t_settings	create_settings(const int count, char **values);
t_settings	*get_settings(const t_settings *set_settings);

// debug.c
void		debug_color(const char *msg, const char *color);
void		success(const char *msg);
void		error(const char *msg);
void		alert(const char *msg);

#endif //PHILOSOPHERS_H
