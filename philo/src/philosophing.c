/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:46:09 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/15 14:49:16 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

void	lock_forks(t_philo *philo)
{
	if (philo->left < philo->right)
	{
		pthread_mutex_lock(philo->left);
		if (access_shared_var(philo->settings.should_stop, 0))
		{
			pthread_mutex_unlock(philo->left);
			return ;
		}
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right);
		if (access_shared_var(philo->settings.should_stop, 0))
		{
			pthread_mutex_unlock(philo->right);
			return ;
		}
		print_state(philo, "has taken a fork");
	}
	else if (philo->left > philo->right)
	{
		pthread_mutex_lock(philo->right);
		if (access_shared_var(philo->settings.should_stop, 0))
		{
			pthread_mutex_unlock(philo->right);
			return ;
		}
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left);
		if (access_shared_var(philo->settings.should_stop, 0))
		{
			pthread_mutex_unlock(philo->left);
			return ;
		}
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left);
		print_state(philo, "has taken a fork");
		while (access_shared_var(philo->settings.should_stop, 0) == 0)
			sleep_ms(2, philo);
		pthread_mutex_unlock(philo->left);
	}
}

void	do_action(t_philo *philo)
{
	if (philo->state == EATING)
	{
		lock_forks(philo);
		if (access_shared_var(philo->settings.should_stop, 0))
			return ;
		access_shared_var((int*)&philo->last_meal, get_current_time_ms(philo->settings.starting_time));
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

int	should_stop(t_philo *philo)
{
	if (access_shared_var(philo->settings.should_stop, 0))
		return (1);
	if (philo->settings.number_of_meal != -1
		&& access_shared_var(&philo->meal_count, 0) >= philo->settings.number_of_meal)
		return (1);
	return (0);
}

void	*philosophing(void *philo_param)
{
	t_philo	*philo;
	int		nb_meal;

	nb_meal = 0;
	philo = (t_philo*)philo_param;
	
	while (!should_stop(philo))
	{
		do_action(philo);
		if (philo->state == EATING)
		{
			nb_meal++;
			access_shared_var(&philo->meal_count, nb_meal);
		}
		philo->state++;
		philo->state %= 3;
	}
	return (NULL);
}