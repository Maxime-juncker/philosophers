/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:35:00 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/11 15:46:56 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

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
	SLEEPING,
	THINKING,
	DEAD,
}	t_state;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	t_state			state;

	t_settings		*settings;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

int			sleep_ms(int ms, t_settings *settings);
long long	get_current_time_ms(void);

// atoi.c
int			overflow_check(const char *s, void (*f)(int, void *), void *param);
int			ft_atoi(const char *nptr);


// philosophing.c
void	*philosophing(void *philo_param);

#endif //PHILOSOPHERS_H
