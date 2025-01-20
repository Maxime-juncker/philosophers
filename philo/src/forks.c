/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:38:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/20 16:07:54 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_fork	**get_forks(t_fork **set_forks)
{
	static t_fork	**forks;

	if (set_forks != NULL)
	{
		if (forks != NULL)
			free(forks);
		forks = set_forks;
		success("fork are created");
	}
	return (forks);
}

int	toggle_fork(t_philosopher *philo, int reset)
{
	t_fork	**forks;
	int		next_id;

	if (get_settings(NULL)->number_of_philosophers == 1)
		return (0);
	next_id = philo->id + 1 % get_settings(NULL)->number_of_philosophers;
	forks = get_forks(NULL);
	pthread_mutex_lock(&(*forks)[philo->id].mutex);
	if (reset == 1)
	{
		(*forks)[philo->id].is_used = 0;
		(*forks)[next_id].is_used = 0;
		pthread_mutex_unlock(&(*forks)[philo->id].mutex);
		return (0);
	}
	// printf("%s%d: %d %d: %d%s\n", RED, philo->id, (*forks)[philo->id].is_used, next_id, (*forks)[next_id].is_used, RESET);
	if ((*forks)[philo->id].is_used == 1 || (*forks)[next_id].is_used == 1)
	{
		pthread_mutex_unlock(&(*forks)[philo->id].mutex);
		return (0);
	}
	(*forks)[philo->id].is_used = 1;
	(*forks)[next_id].is_used = 1;
	print_state(philo, "has taken a fork");
	pthread_mutex_unlock(&(*forks)[philo->id].mutex);
	return (1);
}
