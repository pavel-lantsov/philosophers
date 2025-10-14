#include "philosophers.h"

int	is_dead(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->death);
	res = data->stop_flag;
	pthread_mutex_unlock(&data->death);
	return (res);
}

void	stop(t_data *data)
{
	pthread_mutex_lock(&data->death);
	data->stop_flag = 1;
	pthread_mutex_unlock(&data->death);
}
void	*death_monitor(void *arg)
{
	t_phil	*phils;
	t_data	*data;
	long	cur_time;
	int	i;

	phils = (t_phil *)arg;
	data = phils[0].data;

	while (!is_dead(data))
	{
		i = 0;
		cur_time = get_timestamp();
		while (i < data->num_of_phil && !is_dead(data))
		{
			if (cur_time - phils[i].last_meal_time > data->time_to_die)
			{
				safe_print(&phils[i], "died");
				stop(data);
				break ;
			}
			i++;
		}
		ft_usleep(1);
	}
	return(NULL);
}
