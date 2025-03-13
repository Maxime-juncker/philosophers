/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:11:15 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/13 18:15:11 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <sys/time.h>
#include <unistd.h>

long long	get_current_time_ms(long long starting_time)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time - starting_time);
}

int	sleep_ms(int ms, t_settings *settings)
{
	long long	end_sleep;

	end_sleep = get_current_time_ms(settings->starting_time) + ms;
	while (get_current_time_ms(settings->starting_time) < end_sleep && settings->should_stop == 0)
		usleep(100);
	return (0);
}
