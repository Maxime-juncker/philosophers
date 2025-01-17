#include "philosophers.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_philosopher	*philos;
	t_fork			*forks;
	t_settings		settings;
	struct timeval	tv;
	philos = NULL;
	forks = NULL;
	argc--;
	argv++;
	settings = create_settings(argc, argv);
	get_settings(&settings);
	init(&philos, &forks, settings);
	get_forks(&forks);
	success("philosopher are created !!");

	int	i = 0;
	while (i < settings.number_of_philosophers)
	{
		// printf("id: %d\n", philos[i].id);
		gettimeofday(&tv, NULL);
		philos[i].last_action = tv.tv_usec;
		if (pthread_create(&philos[i].thread, NULL, philosophing, (void *)(&philos[i])) != 0)
		{
			alert("thread creation failed");
			exit(1);
		}
		usleep(settings.time_to_eat);
		i++;
	}

	i = 0;
	while (i < settings.number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) == EDEADLK)
		{
			alert("A deadlock is detected !!");
		}
		i++;
	}
	success("thread are rejoined");

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
	i = 0;
	while (i < get_settings(NULL).number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) == EDEADLK)
		{
			alert("A deadlock is detected !!");
		}
		i++;
	}
	exit(0);
}

t_settings	create_settings(const int count, char **values)
{
	t_settings	settings;

	settings.number_of_philosophers = ft_atoi(values[0]);
	settings.time_to_die 			= ft_atoi(values[1]); // 4u
	settings.time_to_eat 			= ft_atoi(values[2]); // 1u
	settings.time_to_sleep			= ft_atoi(values[3]);
	if (count == 5)
		settings.number_of_time_each_philosopher_must_eat = ft_atoi(values[4]);
	else
		settings.number_of_time_each_philosopher_must_eat = -1;
	return (settings);
}

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

		(*forks)[i].id = i;
		(*forks)[i].is_used = 0;
		pthread_mutex_init(&(*forks)[i].mutex, NULL);
		i++;
	}
}

t_settings	get_settings(const t_settings *set_settings)
{
	static t_settings	settings;

	if (set_settings != NULL)
		settings = *set_settings;
	return (settings);
}

void	print_state(const t_philosopher *philo, const char *msg)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("%ld %d %s\n", tv.tv_usec, philo->id, msg);
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

	if (philo->id + 1 == get_settings(NULL).number_of_philosophers)
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

void	do_action(t_philosopher *philo, t_action action)
{
	struct timeval end_action;

	gettimeofday(&end_action, NULL);
	if (end_action.tv_usec - philo->last_action >= get_settings(NULL).time_to_die)
	{
		print_state(philo, "died");
		alert("a philosopher starved.");
		philo->is_ded = 1;
		return ;
	}
	if (action == EATING)
	{
		while (toggle_fork(philo, 0) == 0)
			usleep(1);
		print_state(philo, "is eating");
		if (usleep(get_settings(NULL).time_to_eat) != 0)
			alert("sleep failed");
		toggle_fork(philo, 1);
	}
	else if (action == SLEEPING)
	{
		print_state(philo, "is sleeping");
		if (usleep(get_settings(NULL).time_to_sleep) != 0)
			alert("sleep failed");
	}
	else if (action == THINKING)
	{
		print_state(philo, "is thinking");
	}
	gettimeofday(&end_action, NULL);
	if (end_action.tv_usec - philo->last_action >= get_settings(NULL).time_to_die && action != EATING)
	{
		print_state(philo, "died");
		alert("a philosopher starved.");
		philo->is_ded = 1;
		return ;
	}
	philo->last_action = end_action.tv_usec;
}
void	*philosophing(void *param_philo)
{
	int	i = 0;
	t_philosopher	*philo;

	philo = (t_philosopher *)param_philo;
	// success("philo is running");
	while ((get_settings(NULL).number_of_time_each_philosopher_must_eat == -1 || \
		i < get_settings(NULL).number_of_time_each_philosopher_must_eat) \
		&& philo->is_ded == 0)
	{
		do_action(philo, EATING);
		if (philo->is_ded == 1)
			end(NULL) ;
		do_action(philo, SLEEPING);
		if (philo->is_ded == 1)
			end(NULL) ;
		do_action(philo, THINKING);
		if (philo->is_ded == 1)
			end(NULL) ;
		if (usleep(50) != 0)
			alert("sleep failed");
		i++;
	}
	// pthread_detach(philo->thread);
	return (NULL);
}
