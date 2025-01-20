#include <philosophers.h>

int	get_time_left(const t_philosopher *philo)
{
	return (get_settings(NULL)->time_to_die - (get_current_time_ms() - philo->last_meal));
}

long get_current_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/*
	@note could error if ms > 1,000
*/
int	sleep_ms(int ms)
{
	if (usleep(ms * 1000) != 0)
	{
		alert("sleep failed");
		return (1);
	}
	return (0);
}