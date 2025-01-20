#include <philosophers.h>

t_fork	**get_forks(t_fork **set_forks)
{
	static t_fork	**forks;

	if (set_forks != NULL)
	{
		if (forks != NULL)
			free(forks);
		forks = set_forks;
	}
	return (forks);
}

int	toggle_fork(t_philosopher *philo, int reset)
{
	t_fork	**forks;
	int		next_id;

	if (get_settings(NULL)->number_of_philosophers == 1)
		return (0);

	if (philo->id + 1 == get_settings(NULL)->number_of_philosophers)
		next_id = 0;
	else
		next_id = philo->id + 1;

	forks = get_forks(NULL);
	pthread_mutex_lock(&(*forks)[philo->id].mutex);
	if (reset == 1)
	{
		(*forks)[philo->id].is_used = 0;
		(*forks)[next_id].is_used = 0;
		pthread_mutex_unlock(&(*forks)[philo->id].mutex);
		return (0);
	}
	// failed to take fork
	if ((*forks)[philo->id].is_used == 1 || (*forks)[next_id].is_used == 1)
	{
		pthread_mutex_unlock(&(*forks)[philo->id].mutex);
		return (0);
	}
	(*forks)[philo->id].is_used = 1;
	(*forks)[next_id].is_used = 1;

	print_state(philo, "has taken a fork");
	pthread_mutex_unlock(&(*forks)[philo->id].mutex);

	// success("philo succed to take a fork");
	return (1);
}
