/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:11:15 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/16 10:40:18 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <sys/time.h>
#include <unistd.h>

unsigned int	get_current_time_ms(long long starting_time)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time - starting_time);
}

int	is_dead(t_philo *philo)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	int						res;

	pthread_mutex_lock(&lock);
	res = get_current_time_ms(philo->settings.starting_time)
		- access_shared_var((int*)&philo->last_meal, 0);
	pthread_mutex_unlock(&lock);
	return (res >= philo->settings.time_to_die);
}

int	sleep_ms(int ms, t_philo *philo)
{
	long long	end_sleep;

	end_sleep = get_current_time_ms(philo->settings.starting_time) + ms;
	while (get_current_time_ms(philo->settings.starting_time) < end_sleep
		&& access_shared_var(philo->settings.should_stop, 0) == 0)
	{
		usleep(100);
	}
	return (0);
}
