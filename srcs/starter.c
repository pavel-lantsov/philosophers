#include "philosophers.h"

int start(t_phil *phils, t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_timestamp();
    while (i < data->number_of_philosophers)
    {
        phils[i].last_meal_time = data->start_time;
        if (pthread_create(&phils[i].thread, NULL, philosopher_routine, &phils[i]) != 0)
        {
            ft_log("Error: Failed to create thread");
            return (0);
        }
        i++;
    }
    return (1);
}