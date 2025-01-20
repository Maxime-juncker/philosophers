#include "philosophers.h"

static int	check_dead(t_philosopher *philo)
{
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
		}
		print_state(philo, "is eating");
		philo->last_meal = get_current_time_ms();
		sleep_ms(get_settings(NULL)->time_to_eat);
		if (check_dead(philo))
			return ;
		toggle_fork(philo, 1);

	}
	else if (action == SLEEPING)
	{
		print_state(philo, "is sleeping");
		sleep_ms(get_settings(NULL)->time_to_sleep);
	}
	else if (action == THINKING)
	{
		print_state(philo, "is thinking");
		sleep_ms(1);
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
