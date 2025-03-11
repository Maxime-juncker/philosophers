/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:35:03 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/11 14:58:39 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// void	print_state(t_philo *philo, const char *msg)
// {
// 	static int	stop_printing;

// 	pthread_mutex_lock(&philo->mutex.print_mutex);
// 	if (stop_printing)
// 	{
// 		pthread_mutex_unlock(&philo->mutex.print_mutex);
// 		return ;
// 	}
// 	printf("%lld\t%d\t%s\n", get_current_time_ms(), philo->id, msg);
// 	if (philo->state == DEAD)
// 	{
// 		stop_printing = 1;
// 	}
// 	pthread_mutex_unlock(&philo->mutex.print_mutex);
// }
