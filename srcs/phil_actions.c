#include "philosophers.h"

static void	ph_take_fork(t_phil *phil, int fork)
{
	if (is_dead(phil->data))
			return ;
	pthread_mutex_lock(&phil->data->forks[fork]);
	safe_print(phil, "has taken a fork");
}

static void eat_alone(t_phil *phil)
{
	ph_take_fork(phil, phil->left_fork);
	ft_usleep(phil->data->time_die + 10);
	pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
}

static void	ph_eat(t_phil *phil)
{	
	if (is_dead(phil->data))
			return ;
	if(phil->data->num_phil == 1)
		eat_alone(phil);
	else
	{
		if (phil->id % 2 == 0)
		{
			ph_take_fork(phil, phil->left_fork);
			ph_take_fork(phil, phil->right_fork);
		}
		else
		{
			ph_take_fork(phil, phil->right_fork);	
			ph_take_fork(phil, phil->left_fork);
		}
		safe_print(phil, "is eating");
		phil->lst_meal_time = get_timestamp();
		ft_usleep(phil->data->time_eat);
		phil->meals++;
		pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
		pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
	}
}

void	*phil_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (!is_dead(phil->data))
	{
		if (!is_dead(phil->data))
			ph_eat(phil);
		if (!is_dead(phil->data))
		{
			safe_print(phil, "is sleeping");
			ft_usleep(phil->data->time_slp);
		}
		if (!is_dead(phil->data))
		{
			safe_print(phil, "is sleeping");
			ft_usleep(phil->data->time_slp);
		}
	}
	return (NULL);
}
