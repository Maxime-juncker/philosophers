/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:58:45 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/16 10:27:53 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <unistd.h>

t_settings	create_settings(const int count, char **values, int *stop_ref)
{
	t_settings	settings;
	
	settings.number_of_philosophers = ft_atoi(values[0]);
	settings.time_to_die = ft_atoi(values[1]);
	settings.time_to_eat = ft_atoi(values[2]);
	settings.time_to_sleep = ft_atoi(values[3]);
	if (count == 5)
		settings.number_of_meal = ft_atoi(values[4]);
	else
		settings.number_of_meal = -1;
	settings.should_stop = stop_ref;
	settings.starting_time = get_current_time_ms(0);
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

int	access_shared_var(int *var, int value)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	int						res;

	pthread_mutex_lock(&lock);
	if (value != 0)
		*var = value;
	res = *var;
	pthread_mutex_unlock(&lock);
	return (res);
}

int	setup(t_philo **philos, t_settings settings)
{
	int	i;

	i = 0;
	while (i < settings.number_of_philosophers)
	{
		philos[i] = calloc(1, sizeof(t_philo));
		if (!philos[i])
			return (clear_philo(philos), -1);
		philos[i]->id = i;
		philos[i]->meal_count = 0;
		philos[i]->settings = settings;
		if (i % 2 == 0 && i + 1 < settings.number_of_philosophers)
			philos[i]->state = EATING;
		else
			philos[i]->state = THINKING;
		philos[i]->left = malloc(sizeof(pthread_mutex_t));
		if (!philos[i]->left)
		{
			free(philos[i]);
			philos[i] = NULL;
			return (clear_philo(philos), -1);
		}
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
			&& access_shared_var(&(philos[i]->meal_count), 0) >= settings.number_of_meal)
			nb_finished++;
		i++;
	}
	if (nb_finished == settings.number_of_philosophers)
	{
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
		philos[i]->right = philos[(i + 1) % settings.number_of_philosophers]->left;
		pthread_create(&(philos[i]->thread), NULL, &philosophing, (void *)philos[i]);
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
		pthread_mutex_lock(philos[i]->left);
		pthread_mutex_unlock(philos[i]->left);
		pthread_mutex_destroy(philos[i]->left);
		pthread_join(philos[i]->thread, NULL);
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
	settings = create_settings(argc - 1, &argv[1], &stop);
	philo = calloc(settings.number_of_philosophers, sizeof(t_philo *));
	if (!philo)
		return (-1);
	if (setup(philo, settings) == -1)
		return (-1);
	run_philo(philo, settings);
	while (1)
	{
		if (stop_philo(philo, settings) == 1)
			break;
		usleep(100);
	}
	shutdown(philo, settings);	
}
