/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:35:00 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/15 13:22:11 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

# define RESET	"\033[0m"
# define GRAY	"\033[90m"
# define BLUE	"\033[0;34m"
# define GET_VARIABLE_NAME(Variable) (#Variable)

typedef struct s_locks
{
	pthread_mutex_t	lock_time;
	pthread_mutex_t	lock_print;
}	t_locks;

typedef struct s_settings
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meal;
	t_locks	*locks;
	int	*should_stop;
	long long	starting_time;
}	t_settings;

typedef enum e_state
{
	EATING = 0,
	SLEEPING,
	THINKING,
	DEAD,
}	t_state;

typedef struct s_philo
{
	int				id;
	unsigned int	last_meal;
	int				meal_count;
	
	t_state			state;

	t_settings		settings;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

int				sleep_ms(int ms, t_philo *philo);
int				is_dead(t_philo *philo);
unsigned int	get_current_time_ms(long long starting_time);

// atoi.c
int				overflow_check(const char *s, void (*f)(int, void *), void *param);
int				ft_atoi(const char *nptr);

// philosophing.c
void			*philosophing(void *philo_param);

// utils.c
void			print_state(t_philo *philo, const char *msg);
void			print_settings(t_settings settings);

int	access_shared_var(int *var, int value);

#endif //PHILOSOPHERS_H
