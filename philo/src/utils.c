/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:35:03 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/15 13:23:10 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	print_state(t_philo *philo, const char *msg)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	printf("%u\t%d\t%s\n", get_current_time_ms(philo->settings.starting_time), philo->id, msg);
	pthread_mutex_unlock(&lock);
}

void	print_settings(t_settings settings)
{
	printf("%ssettings:\n", GRAY);
	printf("%s:%d\n", GET_VARIABLE_NAME(settings.number_of_philosophers), settings.number_of_philosophers);
	printf("%s:%d\n", GET_VARIABLE_NAME(settings.time_to_die), settings.time_to_die);
	printf("%s:%d\n", GET_VARIABLE_NAME(settings.time_to_eat), settings.time_to_eat);
	printf("%s:%d\n", GET_VARIABLE_NAME(settings.time_to_sleep), settings.time_to_sleep);
	printf("%s:%d\n", GET_VARIABLE_NAME(settings.number_of_meal), settings.number_of_meal);
	printf("%s:%lld\n", GET_VARIABLE_NAME(settings.starting_time), settings.starting_time);
	printf("%s\n", RESET);
}
