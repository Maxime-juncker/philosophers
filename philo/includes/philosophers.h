/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:35:00 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/18 13:15:36 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
#include <string.h>

# define RESET	"\033[0m"
# define RED	"\033[0;31m"

typedef struct s_settings
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meal;
	int			*should_stop;
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
int				setup(t_philo **philos, t_settings settings);

// atoi.c
int				get_settings_val(const char *s);

// philosophing.c
void			*philosophing(void *philo_param);

// utils.c
void			print_state(t_philo *philo, const char *msg);
int				access_shared_var(int *var, int value);
void			clear_philo(t_philo **philos);

#endif //PHILOSOPHERS_H	
