/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:46:09 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/11 15:50:27 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*philosophing(void *philo_param)
{
	t_philo	*philo;

	philo = (t_philo*)philo_param;
	printf("%d has begin philosophing\n", philo->id);
}