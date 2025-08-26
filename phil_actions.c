#include "philosophers.h"

static void ph_think(t_phil *phil)
{
    printf("Phil %d is thinking\n", phil->id);
    ft_usleep(1000);
}

void *philosopher_routine(void *arg)
{
    t_phil *phil;

    phil = (t_phil *)arg;
    int i = 0;
    while (i != 3)
    {
        ph_think(phil);
        i++;
    }
}
