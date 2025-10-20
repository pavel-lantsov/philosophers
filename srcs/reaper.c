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

void	die(t_phil *phils, t_data *data)
{
	long	time;

	pthread_mutex_lock(&phils->data->print);
	stop(data);
	if (is_dead(phils->data))
	{
		time = get_timestamp() - phils->data->start_time;
		printf("%ld %d %s\n", time, phils->id, "died");
	}
}

static int	check_phills(t_phil *phils, t_data *data)
{
	long	cur_time;
	int		i;
	int		full;

	i = 0;
	cur_time = get_timestamp();
	full = 0;
	while (i < data->num_phil && !is_dead(data))
	{
		if (cur_time - phils[i].lst_meal_time > data->time_die)
		{
			die(phils, data);
			return (1);
		}
		if (data->must_eaten != -1 && phils[i].meals >= data->must_eaten)
			full++;
		i++;
	}
	if (data->must_eaten > 0 && full == data->num_phil)
	{
		pthread_mutex_lock(&phils->data->print);
		stop(data);
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_phil	*phils;
	t_data	*data;

	phils = (t_phil *)arg;
	data = phils[0].data;
	while (!is_dead(data))
	{
		check_phills(phils, data);
		ft_usleep(1);
	}
	pthread_mutex_unlock(&phils->data->print);
	return (NULL);
}
