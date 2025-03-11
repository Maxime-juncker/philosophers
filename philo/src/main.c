/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:13:39 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/11 13:16:36 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	should_stop(t_philosopher *philos, t_settings *settings)
{
	int	i;
	
	i = 0;
	while (i < settings->number_of_philosophers)
	{
		if (get_time_left(&philos[i]) <= 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	run(t_philosopher *philos)
{
	int				i;
	struct timeval	tv;
	t_settings		*settings;

	settings = get_settings(NULL);
	i = 0;
	while (i < settings->number_of_philosophers)
	{
		gettimeofday(&tv, NULL);
		philos[i].last_meal = get_current_time_ms();
		if (pthread_create(&philos[i].thread, NULL, philosophing, \
			(void *)(&philos[i])) != 0)
		{
			alert("thread creation failed");
			return (1);
		}
		i++;
	}
	while (settings->should_stop == 0)
	{
		usleep(2 * 1000);
		settings->should_stop = should_stop(philos, settings);
	}
	return (0);
}

int	shutdown(t_philosopher *philos, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < get_settings(NULL)->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) == EDEADLK)
		{
			alert("A deadlock is detected !!");
			return (EXIT_FAILURE);
		}
		i++;
	}
	free(philos);
	free(forks);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philosopher	*philos;
	t_fork			*forks;
	t_settings		settings;
	t_mutex_ref		ref;
	int				code;

	if (check_errors(argc - 1, &argv[1]) == 1)
		return (EXIT_FAILURE);
	settings = create_settings(argc - 1, &argv[1]);
	get_settings(&settings);
	code = create_philos_forks(&philos, &forks);
	if (code == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_mutex_init(&ref.print_mutex, NULL);
	init(&philos, &forks, &ref);
	code = run(philos);
	if (code == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (shutdown(philos, forks));
}
