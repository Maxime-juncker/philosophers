/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:35:03 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/24 15:50:20 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	access_shared_var(int *var, int value)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	int						res;

	pthread_mutex_lock(&lock);
	if (value != 0)
		*var = value;
	res = *var;
	pthread_mutex_unlock(&lock);
	return (res);
}

void	clear_philo(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (philos[i]->left)
		{
			pthread_mutex_destroy(philos[i]->left);
			free(philos[i]->left);
		}
		free(philos[i]);
		i++;
	}
	free(philos);
}

int	setup_fork(t_philo **philos, int i)
{
	philos[i]->left = malloc(sizeof(pthread_mutex_t));
	if (!philos[i]->left)
	{
		free(philos[i]);
		philos[i] = NULL;
		return (clear_philo(philos), -1);
	}
	if (pthread_mutex_init(philos[i]->left, NULL) != 0)
	{
		free(philos[i]->left);
		philos[i]->left = NULL;
		return (clear_philo(philos), -1);
	}
	return (0);
}

void	cpy_settings(t_settings *s1, t_settings s2)
{
	s1->number_of_philosophers = s2.number_of_philosophers;
	s1->time_to_die = s2.time_to_die;
	s1->time_to_eat = s2.time_to_eat;
	s1->time_to_sleep = s2.time_to_sleep;
	s1->number_of_meal = s2.number_of_meal;
	s1->should_stop = s2.should_stop;
	s1->starting_time = s2.starting_time;
}

int	setup(t_philo **philos, t_settings settings)
{
	int	i;

	i = 0;
	while (i < settings.number_of_philosophers)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (clear_philo(philos), -1);
		philos[i]->id = i;
		philos[i]->meal_count = 0;
		philos[i]->last_meal = 0;
		cpy_settings(&philos[i]->settings, settings);
		philos[i]->state = THINKING;
		if (setup_fork(philos, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}
