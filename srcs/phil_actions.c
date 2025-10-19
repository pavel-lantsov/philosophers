#include "philosophers.h"

void	ph_take_fork(t_phil *phil)
{
	if(phil->id %2 == 0)
	{
		pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
		safe_print(phil, "has taken a fork");
		pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
		safe_print(phil, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
		safe_print(phil, "has taken a fork");
		pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
		safe_print(phil, "has taken a fork");
	}
}

static void	ph_think(t_phil *phil)
{
	safe_print(phil, "is thinking");
}

static void	ph_eat(t_phil *phil)
{
	ph_take_fork(phil);
	safe_print(phil, "is eating");
	phil->lst_meal_time = get_timestamp();
	ft_usleep(phil->data->time_eat);
	phil->meals++;
	pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
}

static void	ph_sleep(t_phil *phil)
{
	safe_print(phil, "is sleeping");
	ft_usleep(phil->data->time_slp);
}

void	*phil_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (!is_dead(phil->data))
	{
		if (is_dead(phil->data))
            break ;
		ph_think(phil);
		if (is_dead(phil->data))
            break ;
		ph_eat(phil);
		if (is_dead(phil->data))
            break ;
		ph_sleep(phil);
	}
	return (NULL);
}
