#include <philosophers.h>

long get_current_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

t_settings	create_settings(const int count, char **values)
{
	t_settings	settings;

	settings.number_of_philosophers = ft_atoi(values[0]);
	settings.time_to_die 			= ft_atoi(values[1]);
	settings.time_to_eat 			= ft_atoi(values[2]) * 1000;
	settings.time_to_sleep			= ft_atoi(values[3]) * 1000;
	if (count == 5)
		settings.number_of_time_each_philosopher_must_eat = ft_atoi(values[4]);
	else
		settings.number_of_time_each_philosopher_must_eat = -1;
	settings.should_stop = 0;
	return (settings);
}

t_settings	*get_settings(const t_settings *set_settings)
{
	static t_settings	settings;

	if (set_settings != NULL)
		settings = *set_settings;
	return (&settings);
}
int	get_time_left(const t_philosopher *philo)
{
	return (get_settings(NULL)->time_to_die - (get_current_time_ms() - philo->last_meal));
}

void	print_state(const t_philosopher *philo, const char *msg)
{
	struct timeval	tv;
	int				i;

	i = 0;
	while (i < get_settings(NULL)->number_of_philosophers)
	{
		if (philo->other_philos[i].is_ded == 1)
			return ;
		i++;
	}
	gettimeofday(&tv, NULL);
	printf("%ld %d %s\n", get_current_time_ms(), philo->id, msg);

	// printf("%ld %d %s (time left: %d)\n", get_current_time_ms(), philo->id, msg, get_time_left(philo));
}