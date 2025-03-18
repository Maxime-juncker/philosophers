/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:46:09 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/18 10:03:25 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

int	lock_forks(t_philo *philo, pthread_mutex_t *left, pthread_mutex_t *right)
{
	if (right == NULL)
	{
		pthread_mutex_lock(left);
		print_state(philo, "has taken a fork");
		while (access_shared_var(philo->settings.should_stop, 0) == 0)
			sleep_ms(2, philo);
		pthread_mutex_unlock(left);
		return (1);
	}
	pthread_mutex_lock(left);
	if (access_shared_var(philo->settings.should_stop, 0))
	{
		pthread_mutex_unlock(left);
		return (1);
	}
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(right);
	if (access_shared_var(philo->settings.should_stop, 0))
	{
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(right);
		return (1);
	}
	print_state(philo, "has taken a fork");
	return (0);
}

int	get_forks(t_philo *philo)
{
	if (philo->left < philo->right)
	{
		return (lock_forks(philo, philo->left, philo->right));
	}
	else if (philo->left > philo->right)
	{
		return (lock_forks(philo, philo->right, philo->left));
	}
	else
	{
		return (lock_forks(philo, philo->left, NULL));
	}
	return (0);
}

void	do_action(t_philo *philo)
{
	if (philo->state == EATING)
	{
		if (get_forks(philo) == 1)
			return ;
		access_shared_var((int *)&philo->last_meal,
			get_current_time_ms(philo->settings.starting_time));
		print_state(philo, "is eating");
		sleep_ms(philo->settings.time_to_eat, philo);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
	else if (philo->state == THINKING)
	{
		print_state(philo, "is thinking");
	}
	else if (philo->state == SLEEPING)
	{
		print_state(philo, "is sleeping");
		sleep_ms(philo->settings.time_to_sleep, philo);
	}
}

void	*philosophing(void *philo_param)
{
	t_philo	*philo;
	int		nb_meal;

	nb_meal = 0;
	philo = (t_philo *)philo_param;
	while (!access_shared_var(philo->settings.should_stop, 0))
	{
		do_action(philo);
		if (philo->state == EATING)
		{
			nb_meal++;
			if (philo->settings.number_of_meal != -1
				&& nb_meal >= philo->settings.number_of_meal)
			{
				access_shared_var(&philo->meal_count, nb_meal);
			}
		}
		philo->state++;
		philo->state %= 3;
	}
	return (NULL);
}
