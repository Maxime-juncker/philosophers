/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:10:35 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/20 15:47:52 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death(t_philosopher *philo)
{
	t_settings	*settings;

	settings = get_settings(NULL);
	if (get_time_left(philo) <= 0)
	{
		print_state(philo, "died");
		settings->should_stop = 1;
		return (1);
	}
	return (0);
}

void	eat(t_philosopher *philo)
{
	while (toggle_fork(philo, 0) == 0)
	{
		if (check_death(philo))
			return ;
	}
	print_state(philo, "is eating");
	philo->last_meal = get_current_time_ms();
	sleep_ms(get_settings(NULL)->time_to_eat);
	if (check_death(philo))
		return ;
	toggle_fork(philo, 1);
}

void	do_action(t_philosopher *philo, t_state action)
{
	if (action == EATING)
	{
		eat(philo);
	}
	else if (action == SLEEPING)
	{
		print_state(philo, "is sleeping");
		sleep_ms(get_settings(NULL)->time_to_sleep);
	}
	else if (action == THINKING)
	{
		print_state(philo, "is thinking");
		sleep_ms(1);
	}
	if (check_death(philo))
		return ;
}

void	*philosophing(void *param_philo)
{
	int				i;
	t_philosopher	*philo;
	t_settings		*settings;

	i = 0;
	philo = (t_philosopher *)param_philo;
	settings = get_settings(NULL);
	while ((settings->number_of_time_each_philosopher_must_eat == -1 || \
		i < settings->number_of_time_each_philosopher_must_eat) || \
		settings->should_stop == 1)
	{
		do_action(philo, philo->state);
		if (settings->should_stop == 1)
			return (NULL);
		if (philo->state == THINKING)
			philo->state = EATING;
		else
			philo->state++;
		i++;
	}
	return (NULL);
}
