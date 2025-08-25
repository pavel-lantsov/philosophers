#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

typedef struct	s_data
{
    int		number_of_philosophers;
    long	time_to_die;
    long	time_to_eat;
    long	time_to_sleep;
} t_data;

void ft_log(char* s);
long get_timestamp(void);
void ft_usleep(long ms);
long ft_atol(const char *str);
int parse_args(int argc, char *argv[], t_data *data);
