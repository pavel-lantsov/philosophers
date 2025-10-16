#include "philosophers.h"

void	safe_print(t_phil *phil, char *action)
{
	long	time;

	time = get_timestamp() - phil->data->start_time;
	pthread_mutex_lock(&phil->data->print);
	printf("%ld %d %s\n", time, phil->id, action);
	pthread_mutex_unlock(&phil->data->print);
}
static void	ph_think(t_phil *phil)
{
	safe_print(phil, "is thinking");
}
static void	ph_eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
	safe_print(phil, "has taken a fork");
	pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
	safe_print(phil, "has taken a fork");
	safe_print(phil, "is eating");
	phil->last_meal_time = get_timestamp();
	ft_usleep(phil->data->time_to_eat);
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
}

static void	ph_sleep(t_phil *phil)
{
	safe_print(phil, "is sleeping");
	ft_usleep(phil->data->time_to_sleep);
}

void	*phil_routine(void *arg)
{
	t_phil *phil;

	phil = (t_phil *)arg;
	while (!is_dead(phil->data))
	{
		ph_think(phil);
		ph_eat(phil);
		ph_sleep(phil);
	}
	return (NULL);
}
