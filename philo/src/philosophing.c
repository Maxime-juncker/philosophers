/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:46:09 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/13 18:26:41 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

void	do_action(t_philo *philo)
{
	
}

void	*philosophing(void *philo_param)
{
	t_philo	*philo;

	philo = (t_philo*)philo_param;
	print_state(philo, "has begin philosophing");

	sleep(1);
	printf("ttd: %d\n", *(philo->settings.should_stop));
	print_state(philo, "has stop philosophing");
	return (NULL);
}