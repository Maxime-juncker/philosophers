/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:10:35 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/06 08:57:49 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philosopher *philo, t_settings *settings)
{
	if (get_time_left(philo) <= 0)
	{
		philo->state = DEAD;
		settings->should_stop = 1;
		print_state(philo, "died");
		return (1);
	}
	return (0);
}

void	eat(t_philosopher *philo, t_settings *settings)
{
	while (toggle_fork(philo, 0) == 0)
	{
		if (check_death(philo, settings))
			return ;
		usleep(50);
		continue;
	}
	print_state(philo, "is eating");
	philo->last_meal = get_current_time_ms();
	sleep_ms(get_settings(NULL)->time_to_eat, settings);
	if (check_death(philo, settings))
		return ;
	toggle_fork(philo, 1);
}

void	do_action(t_philosopher *philo, t_state action, t_settings *settings)
{
	if (action == EATING)
	{
		eat(philo, settings);
		philo->meal_eaten++;
	}
	else if (action == SLEEPING)
	{
		print_state(philo, "is sleeping");
		sleep_ms(get_settings(NULL)->time_to_sleep, settings);
	}
	else if (action == THINKING)
	{
		print_state(philo, "is thinking");
		sleep_ms(1, settings);
	}
	if (check_death(philo, settings))
	{
		return ;
	}
}

void	*philosophing(void *param_philo)
{
	t_philosopher	*philo;
	t_settings		*settings;

	philo = (t_philosopher *)param_philo;
	settings = get_settings(NULL);
	while ((settings->number_of_time_each_philosopher_must_eat == -1 || \
		philo->meal_eaten < settings->number_of_time_each_philosopher_must_eat) \
		|| settings->should_stop == 1)
	{
		do_action(philo, philo->state, settings);
		if (settings->should_stop == 1)
			return (NULL);
		if (philo->state == THINKING)
			philo->state = EATING;
		else
			philo->state++;
	}
	return (NULL);
}
