/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:54:30 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/11 11:50:02 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_settings	create_settings(const int count, char **values)
{
	t_settings	settings;
	struct timeval	tv;
	
	settings.number_of_philosophers = ft_atoi(values[0]);
	settings.time_to_die = ft_atoi(values[1]);
	settings.time_to_eat = ft_atoi(values[2]);
	settings.time_to_sleep = ft_atoi(values[3]);
	if (count == 5)
	settings.number_of_time_each_philosopher_must_eat = ft_atoi(values[4]);
	else
	settings.number_of_time_each_philosopher_must_eat = -1;
	settings.should_stop = 0;
	gettimeofday(&tv, NULL);
	return (settings);
}

t_settings	*get_settings(const t_settings *set_settings)
{
	static t_settings	settings;

	if (set_settings != NULL)
		settings = *set_settings;
	return (&settings);
}
