/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:35:03 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/13 18:16:08 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	print_state(t_philo *philo, const char *msg)
{
	static int	stop_printing = 0;

	if (stop_printing)
		return ;
	printf("%lld\t%d\t%s\n", get_current_time_ms(philo->settings.starting_time), philo->id, msg);
	if (philo->state == DEAD)
	{
		stop_printing = 1;
	}
}
