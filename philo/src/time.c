/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:11:15 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/20 15:11:48 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	get_time_left(const t_philosopher *philo)
{
	return (get_settings(NULL)->time_to_die - \
	(get_current_time_ms() - philo->last_meal));
}

long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*
	@note could error if ms > 1,000
*/
int	sleep_ms(int ms)
{
	if (usleep(ms * 1000) != 0)
	{
		alert("sleep failed");
		return (1);
	}
	return (0);
}
