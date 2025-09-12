#include "philosophers.h"

/*static void ph_think(t_phil *phil)
{
    printf("Phil %d is thinking\n", phil->id);
    ft_usleep(phil->data->time_to_think);
}*/
static void ph_eat(t_phil *phil)
{
    pthread_mutex_lock(&phil->data->forks[phil->left_fork]);
    printf("%ld %d has taken a fork\n", get_timestamp() - phil->data->start_time, phil->id);
    pthread_mutex_lock(&phil->data->forks[phil->right_fork]);
    printf("%ld %d has taken a fork\n", get_timestamp() - phil->data->start_time, phil->id);
    printf("Phil %d is eating\n", phil->id);
    phil->last_meal_time = get_timestamp();
    ft_usleep(phil->data->time_to_eat);
    pthread_mutex_unlock(&phil->data->forks[phil->right_fork]);
    pthread_mutex_unlock(&phil->data->forks[phil->left_fork]);
}
static void ph_sleep(t_phil *phil)
{
    printf("Phil %d is sleeping\n", phil->id);
    ft_usleep(phil->data->time_to_sleep);
}

void *philosopher_routine(void *arg)
{
    t_phil *phil;

    phil = (t_phil *)arg;
    while (!phil->data->stop_flag)
    {
        //ph_think(phil);
        ph_eat(phil);
        ph_sleep(phil);
    }
    return (NULL);
}
