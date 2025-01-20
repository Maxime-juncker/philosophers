#include "philosophers.h"


void	init(t_philosopher **philos, t_fork **forks, t_settings settings)
{
	int	i;

	*philos = malloc(sizeof(t_philosopher) * (settings.number_of_philosophers + 1));
	if (*philos == NULL)
		exit(1);

	*forks = malloc(sizeof(t_fork) * (settings.number_of_philosophers + 1));
	if (*forks == NULL)
	{
		free(philos);
		exit(1);
	}
	i = 0;
	while (i < settings.number_of_philosophers)
	{
		(*philos)[i].id = i;
		(*philos)[i].is_ded = 0;
		(*philos)[i].state = i % 2 == 0 ? EATING : SLEEPING;

		(*forks)[i].id = i;
		(*forks)[i].is_used = 0;
		pthread_mutex_init(&(*forks)[i].mutex, NULL);
		i++;
	}
}

void		end(t_philosopher *set)
{
	static t_philosopher	*philos;
	int						i;

	if (set != NULL)
	{
		philos = set;
		return ;
	}
	success("ending philosophing");
	i = 0;
	while (i < get_settings(NULL)->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) == EDEADLK)
		{
			alert("A deadlock is detected !!");
		}
		i++;
	}
	success("ending philosophing");
	exit(0);
}

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

int	check_dead(t_philosopher *philo)
{
	// if (get_time_left(philo) < 20)
	// 	printf("%s(id: %d) %d%s\n", RED, philo->id, get_time_left(philo), RESET);
	// else
	// 	printf("%s(id: %d) %d%s\n", YELLOW, philo->id, get_time_left(philo), RESET);

	if (get_time_left(philo) <= 0)
	{
		print_state(philo, "died");
		alert("a philosopher starved.");
		philo->is_ded = 1;
		return (1);
	}
	return (0);
}

void	do_action(t_philosopher *philo, t_state action)
{
	if (action == EATING)
	{
		while (toggle_fork(philo, 0) == 0)
		{
			if (check_dead(philo))
				return ;
			// usleep(50 * 1000);
		}
		print_state(philo, "is eating");
		philo->last_meal = get_current_time_ms();
		if (usleep(get_settings(NULL)->time_to_eat) != 0)
			alert("sleep failed");
		if (check_dead(philo))
			return ;
		toggle_fork(philo, 1);

	}
	else if (action == SLEEPING)
	{
		print_state(philo, "is sleeping");
		if (usleep(get_settings(NULL)->time_to_sleep) != 0)
			alert("sleep failed");
	}
	else if (action == THINKING)
	{
		print_state(philo, "is thinking");
	}
	if (check_dead(philo))
		return ;
}
void	*philosophing(void *param_philo)
{
	int	i = 0;
	t_philosopher	*philo;

	philo = (t_philosopher *)param_philo;
	while ((get_settings(NULL)->number_of_time_each_philosopher_must_eat == -1 || \
		i < get_settings(NULL)->number_of_time_each_philosopher_must_eat))
	{
		do_action(philo, philo->state);
		if (philo->is_ded == 1)
			return (NULL);
		if (philo->state == THINKING)
			philo->state = EATING;
		else
			philo->state++;
		i++;
	}
	return (NULL);
}
