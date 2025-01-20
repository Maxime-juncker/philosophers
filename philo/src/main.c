/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:13:39 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/20 15:57:54 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	run(t_philosopher *philos)
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
			exit(1);
		}
		i++;
	}
}

void	end(t_philosopher *philos, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < get_settings(NULL)->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) == EDEADLK)
		{
			alert("A deadlock is detected !!");
		}
		i++;
	}
	free(philos);
	free(forks);
}

int	main(int argc, char **argv)
{
	t_philosopher	*philos;
	t_fork			*forks;
	t_settings		settings;

	settings = create_settings(argc - 1, &argv[1]);
	get_settings(&settings);
	create_philos_forks(&philos, &forks);
	init(&philos, &forks);
	run(philos);
	end(philos, forks);
}
