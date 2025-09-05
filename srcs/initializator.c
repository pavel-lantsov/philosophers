#include "philosophers.h"

t_phil *init_philosophers(t_data *data)
{
	t_phil *philosophers;
	int i;

	philosophers = malloc(sizeof(t_phil) * data->number_of_philosophers);
	if (!philosophers)
		return (NULL);

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		philosophers[i].last_meal_time = data->start_time;
		i++;
	}
	return (philosophers);
}