#include "philosophers.h"

pthread_mutex_t *init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int	i;
	int j;

	forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if(pthread_mutex_init(&forks[i], NULL) != 0)
		{
		j = 0;
            while (j < i)
            {
                pthread_mutex_destroy(&forks[j]);
                j++;
            }
            free(forks);
            return (NULL);
        }
        i++;
	}
	return (forks);
}
t_phil *init_philosophers(t_data *data)
{
	t_phil *philosophers;
	int i;

	data->forks = init_forks(data);
	if(!data->forks)
		return (NULL);
	philosophers = malloc(sizeof(t_phil) * data->number_of_philosophers);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		philosophers[i].last_meal_time = 0;
		philosophers[i].left_fork = i;
		philosophers[i].right_fork = (i + 1) % data->number_of_philosophers;
		i++;
	}
	return (philosophers);
}
