/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:32:03 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/11 13:12:04 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	create_philos_forks(t_philosopher **philos, t_fork **forks)
{
	t_settings	*settings;

	settings = get_settings(NULL);
	*philos = malloc(sizeof(t_philosopher) * \
	(settings->number_of_philosophers));
	if (*philos == NULL)
	{
		error("failed malloc!");
		return (EXIT_FAILURE);
	}
	*forks = malloc(sizeof(t_fork) * (settings->number_of_philosophers));
	if (*forks == NULL)
	{
		error("failed malloc!");
		free(*philos);
		return (EXIT_FAILURE);
	}
	return (0);
}

void	init(t_philosopher **philos, t_fork **forks, t_mutex_ref *refs)
{
	int			i;

	i = 0;
	while (i < get_settings(NULL)->number_of_philosophers)
	{
		(*philos)[i].id = i;
		(*philos)[i].meal_eaten = 0;
		if (i % 2 == 0)
			(*philos)[i].state = EATING;
		else
			(*philos)[i].state = SLEEPING;
		(*philos)[i].mutex = *refs;
		(*forks)[i].id = i;
		(*forks)[i].is_used = 0;
		(*philos)[i].left = &(*forks)[i];
		(*philos)[i].right = &(*forks)[((*philos)[i].id + 1) % (get_settings(NULL)->number_of_philosophers)];
		pthread_mutex_init(&(*forks)[i].mutex, NULL);
		i++;
	}
	get_forks(forks);
}
