#include "philosophers.h"

void	free_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

static pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->num_phil);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->num_phil)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free_forks(forks, i);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static void	init_phil_data(t_phil *phils, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phil)
	{
		phils[i].id = i + 1;
		phils[i].data = data;
		phils[i].lst_meal_time = 0;
		phils[i].left_fork = i;
		phils[i].right_fork = (i + 1) % data->num_phil;
		phils[i].meals = 0;
		i++;
	}
}

void	destroy_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
}

t_phil	*init_phils(t_data *data)
{
	t_phil	*philosophers;

	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&data->death, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		return (NULL);
	}
	data->forks = init_forks(data);
	if (!data->forks)
	{
		destroy_mutex(data);
		return (NULL);
	}
	philosophers = malloc(sizeof(t_phil) * data->num_phil);
	if (!philosophers)
	{
		free_forks(data->forks, data->num_phil);
		destroy_mutex(data);
		return (NULL);
	}
	init_phil_data(philosophers, data);
	return (philosophers);
}
