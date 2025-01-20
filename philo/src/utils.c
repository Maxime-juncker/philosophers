/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:35:03 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/20 15:10:21 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_settings	create_settings(const int count, char **values)
{
	t_settings	settings;

	settings.number_of_philosophers = ft_atoi(values[0]);
	settings.time_to_die = ft_atoi(values[1]);
	settings.time_to_eat = ft_atoi(values[2]);
	settings.time_to_sleep = ft_atoi(values[3]);
	if (count == 5)
		settings.number_of_time_each_philosopher_must_eat = ft_atoi(values[4]);
	else
		settings.number_of_time_each_philosopher_must_eat = -1;
	settings.should_stop = 0;
	return (settings);
}

t_settings	*get_settings(const t_settings *set_settings)
{
	static t_settings	settings;

	if (set_settings != NULL)
		settings = *set_settings;
	return (&settings);
}

void	print_state(const t_philosopher *philo, const char *msg)
{
	struct timeval			tv;
	static pthread_mutex_t	mutex;
	static int				mutex_init = 0;

	if (mutex_init == 0)
	{
		pthread_mutex_init(&mutex, NULL);
		mutex_init = 1;
	}
	pthread_mutex_lock(&mutex);
	if (get_settings(NULL)->should_stop == 1)
	{
		pthread_mutex_unlock(&mutex);
		return ;
	}
	gettimeofday(&tv, NULL);
	printf("%ld %d %s\n", get_current_time_ms(), philo->id, msg);
	pthread_mutex_unlock(&mutex);
}
