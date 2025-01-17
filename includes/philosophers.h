#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>
# include <limits.h>

typedef struct s_settings
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_time_each_philosopher_must_eat;
}	t_settings;

typedef enum e_action
{
	SLEEPING = 0,
	THINKING,
	EATING,
}	t_action;

typedef struct s_philosopher
{
	int					id;
	short int			is_ded;
	long int			last_action;
	pthread_t			thread;
}	t_philosopher;

typedef struct s_fork
{
	int				id;
	int				is_used;
	pthread_mutex_t	mutex;
}	t_fork;


// philosophers.c
t_settings	create_settings(const int count, char **values);
void		init(t_philosopher **philos, t_fork **forks, t_settings settings);
void		*philosophing(void *philo_param);
void		print_state(const t_philosopher *philo, const char * msg);
t_fork		**get_forks(t_fork **set_forks);
int			toggle_fork(t_philosopher *philo, int reset);
t_settings	get_settings(const t_settings *set_settings);

// atoi.c

int			overflow_check(const char *s, void (*f)(int, void *), void *param);
int			ft_atoi(const char *nptr);


// debug.c
void		debug_color(const char *msg, const char *color);
void		success(const char *msg);
void		warning(const char *msg);
void		error(const char *msg);
void		alert(const char *msg);

#endif //PHILOSOPHERS_H
