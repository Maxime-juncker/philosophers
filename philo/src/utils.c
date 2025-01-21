/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:35:03 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/21 08:55:37 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
