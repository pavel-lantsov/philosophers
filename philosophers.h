#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_data
{
    int number_of_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long time_to_think;
    long start_time;
    int stop_flag;
    pthread_mutex_t *forks;
} t_data;

typedef struct s_phil
{
    pthread_t thread;
    t_data *data;
    int id;
    long last_meal_time;
    int left_fork;
    int right_fork;
} t_phil;

int    ft_log(char *s);
void    ft_usleep(long ms);
void    *philosopher_routine(void *arg);
long    get_timestamp(void);
long    ft_atol(const char *str);
t_phil *init_philosophers(t_data *data);
int     start(t_phil *phils, t_data *data);

