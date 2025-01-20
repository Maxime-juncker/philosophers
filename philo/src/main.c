#include <philosophers.h>

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

void		end(t_philosopher *philos)
{
	(void)philos;
}

int	main(int argc, char **argv)
{
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
	end(philos);

	int	i = 0;
	while (i < settings.number_of_philosophers)
	{
		// printf("id: %d\n", philos[i].id);
		gettimeofday(&tv, NULL);
		philos[i].last_meal = get_current_time_ms();
		philos[i].other_philos = philos;
		if (pthread_create(&philos[i].thread, NULL, philosophing, (void *)(&philos[i])) != 0)
		{
			alert("thread creation failed");
			exit(1);
		}
		// usleep(10 * 1000);
		i++;
	}

	i = 0;
	while (i < get_settings(NULL)->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) == EDEADLK)
		{
			alert("A deadlock is detected !!");
		}
		i++;
	}
}