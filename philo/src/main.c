/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:58:45 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/24 10:49:10 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <unistd.h>

int	create_settings(const int count, char **values,
	int *stop_ref, t_settings *settings)
{
	if (count < 4 || count > 5)
	{
		printf("%sinvalid arguments%s\n", RED, RESET);
		return (-1);
	}
	settings->number_of_philosophers = get_settings_val(values[0]);
	settings->time_to_die = get_settings_val(values[1]);
	settings->time_to_eat = get_settings_val(values[2]);
	settings->time_to_sleep = get_settings_val(values[3]);
	if (count == 5)
		settings->number_of_meal = get_settings_val(values[4]);
	else
		settings->number_of_meal = -1;
	if (settings->number_of_philosophers == -1
		|| settings->time_to_die == -1 || settings->time_to_die == -1
		|| settings->time_to_sleep == -1)
		return (-1);
	settings->should_stop = stop_ref;
	settings->starting_time = get_current_time_ms(0);
	return (0);
}

int	stop_philo(t_philo **philos, t_settings settings)
{
	int	i;
	int	nb_finished;

	i = 0;
	nb_finished = 0;
	while (i < settings.number_of_philosophers)
	{
		if (is_dead(philos[i]))
		{
			access_shared_var(settings.should_stop, 1);
			print_state(philos[i], "died");
			return (1);
		}
		if (settings.number_of_meal != -1
			&& access_shared_var(&(philos[i]->meal_count), 0)
			>= settings.number_of_meal)
			nb_finished++;
		i++;
	}
	if (nb_finished >= settings.number_of_philosophers)
	{
		access_shared_var(settings.should_stop, 1);
		return (1);
	}
	return (0);
}

void	run_philo(t_philo **philos, t_settings settings)
{
	int				i;

	i = 0;
	while (i < settings.number_of_philosophers)
	{
		philos[i]->right = philos[(i + 1)
			% settings.number_of_philosophers]->left;
		if (pthread_create(&(philos[i]->thread), NULL, &philosophing, (void *)philos[i]) != 0)
		{
			
		}
		usleep(100);
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
	i = 0;
	while (i < settings.number_of_philosophers)
	{
		pthread_mutex_destroy(philos[i]->left);
		free(philos[i]->left);
		free(philos[i]);
		i++;
	}
	free(philos);
}

int	main(int argc, char **argv)
{
	t_settings	settings;
	t_philo		**philo;
	int			stop;

	stop = 0;
	if (create_settings(argc - 1, &argv[1], &stop, &settings) == -1)
		return (-1);
	philo = malloc(settings.number_of_philosophers * sizeof(t_philo *));
	if (!philo)
		return (-1);
	if (setup(philo, settings) == -1)
		return (-1);
	run_philo(philo, settings);
	while (1)
	{
		if (stop_philo(philo, settings) == 1)
			break ;
		usleep(100);
	}
	shutdown(philo, settings);
}
