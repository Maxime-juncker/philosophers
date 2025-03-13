/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:58:45 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/13 18:15:29 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_settings	create_settings(const int count, char **values, int *stop_ref)
{
	t_settings	settings;
	
	settings.number_of_philosophers = ft_atoi(values[0]);
	settings.time_to_die = ft_atoi(values[1]);
	settings.time_to_eat = ft_atoi(values[2]);
	settings.time_to_sleep = ft_atoi(values[3]);
	if (count == 5)
		settings.number_of_time_each_philosopher_must_eat = ft_atoi(values[4]);
	else
		settings.number_of_time_each_philosopher_must_eat = -1;
	settings.should_stop = stop_ref;
	settings.locks = malloc(sizeof(t_locks));
	// if (settings.locks == NULL)
	// 	return ; //! error here
	settings.starting_time = get_current_time_ms(0);
	pthread_mutex_init(&settings.locks->lock_print, NULL);
	pthread_mutex_init(&settings.locks->lock_time, NULL);
	return (settings);
}

void	clear_philo(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (philos[i]->left)
		{
			pthread_mutex_destroy(philos[i]->left);
			free(philos[i]->left);
		}
		free(philos[i]);
		i++;
	}
	free(philos);
}

int	setup(t_philo **philos, t_settings settings)
{
	int	i;

	i = 0;
	while (i < settings.number_of_philosophers)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (clear_philo(philos), -1);
		philos[i]->id = i;
		philos[i]->settings = settings;
		if (i % 2 == 0)
			philos[i]->state = EATING;
		else
			philos[i]->state = THINKING;
		philos[i]->left = malloc(sizeof(pthread_mutex_t));
		if (!philos[i]->left)
			return (clear_philo(philos), -1);
		if (pthread_mutex_init(philos[i]->left, NULL) != 0)
		{
			free(philos[i]->left);
			philos[i]->left = NULL;
			return (clear_philo(philos), -1);
		}
		i++;
	}
	return (0);
}

void	run_philo(t_philo **philos, t_settings settings)
{
	int	i;

	i = 0;
	while (i < settings.number_of_philosophers)
	{
		philos[i]->right = philos[(i + 1) % settings.number_of_philosophers]->left;
		pthread_create(&(philos[i]->thread), NULL, &philosophing, (void *)philos[i]);
		i++;
	}
}

void	shutdown(t_philo **philos, t_settings settings)
{
	int	i;

	i = 0;
	while (i < settings.number_of_philosophers)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_settings	settings;
	t_philo		**philo;
	int			stop;

	stop = 0;
	settings = create_settings(argc + 1, &argv[1], &stop);
	philo = malloc(sizeof(t_philo *) * settings.number_of_philosophers);
	if (!philo)
		return (-1);
	if (setup(philo, settings) == -1)
		return (-1);
	run_philo(philo, settings);
	shutdown(philo, settings);
	
}