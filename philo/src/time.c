/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:11:15 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/11 15:28:49 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <sys/time.h>
#include <unistd.h>

long long	get_current_time_ms(void)
{
	static long long	starting_time = 0;
	long long			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (starting_time == 0)
		starting_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time - starting_time);
}

int	sleep_ms(int ms, t_settings *settings)
{
	long long	end_sleep;

	end_sleep = get_current_time_ms() + ms;
	while (get_current_time_ms() < end_sleep && settings->should_stop == 0)
		usleep(100);
	return (0);
}
