#include "philosophers.h"

t_settings	create_settings(void);
void		init(t_philosopher **philos, t_fork **forks, t_settings settings);
void		*philosophing(void *philo_param);
void		print_state(const t_philosopher *philo, const char * msg);
t_fork		**get_forks(t_fork **set_forks);
int			toggle_fork(t_philosopher *philo, int reset);

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
	settings = create_settings();
	init(&philos, &forks, settings);
	get_forks(&forks);
	success("philosopher are created !!");

	int	i = 0;
	while (i < settings.number_of_philosophers)
	{
		printf("id: %d\n", philos[i].id);
		gettimeofday(&tv, NULL);
		philos[i].last_action = tv.tv_usec;
		pthread_create(&philos[i].thread, NULL, philosophing, (void *)(&philos[i]));
		i++;
	}

	i = 0;
	while (i < settings.number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	success("thread are rejoined");

}

t_settings	create_settings(void)
{
	t_settings	settings;

	settings.number_of_philosophers = 3;
	settings.time_to_die 			= 100;
	settings.time_to_eat 			= 500;
	settings.time_to_sleep			= 500;
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
		(*philos)[i].settings = settings;

		(*forks)[i].id = i;
		(*forks)[i].is_used = 0;
		pthread_mutex_init(&(*forks)[i].mutex, NULL);
		i++;
	}
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

	if (philo->id + 1 == philo->settings.number_of_philosophers)
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

	if (action == EATING)
	{
		while (toggle_fork(philo, 0) == 0)
			usleep(10);
		print_state(philo, "is eating");
		usleep(philo->settings.time_to_eat);
		toggle_fork(philo, 1);
	}
	else if (action == SLEEPING)
	{
		print_state(philo, "is sleeping");
		usleep(philo->settings.time_to_sleep);
	}
	else if (action == THINKING)
	{
		print_state(philo, "is thinking");
		usleep(philo->settings.time_to_sleep);
	}
	gettimeofday(&end_action, NULL);
	if (end_action.tv_usec - philo->last_action >= philo->settings.time_to_die)
	{
		print_state(philo, "died");
		alert("a philosopher starved.");
		philo->is_ded = 1;
		exit(0); // ! Not the best way to do this
		return ;
	}
	philo->last_action = end_action.tv_usec;
}
void	*philosophing(void *param_philo)
{
	int	i = 0;
	t_philosopher	*philo;

	philo = (t_philosopher *)param_philo;
	success("philo is running");
	while (i < 10 && philo->is_ded == 0)
	{
		do_action(philo, EATING);
		if (philo->is_ded == 1)
			break ;
		do_action(philo, SLEEPING);
		if (philo->is_ded == 1)
			break ;
		do_action(philo, THINKING);
		if (philo->is_ded == 1)
			break ;
		i++;
	}
	pthread_detach(philo->thread);
	return (NULL);
}
