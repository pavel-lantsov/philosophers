#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct	s_data
{
	int				num_of_phil;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	long			start_time;
	int				stop_flag;
	long			must_eat_count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
} t_data;

typedef struct s_phil
{
	pthread_t thread;
	t_data *data;
	int id;
	long last_meal_time;
	int left_fork;
	int right_fork;
	int meals_eaten;
} t_phil;

int		ft_log(char *s);
void	ft_usleep(long ms);
void	*phil_routine(void *arg);
void	stop(t_data *data);
void	safe_print(t_phil *phil, char *action);
long	get_timestamp(void);
int		is_dead(t_data *data);
void	*death_monitor(void *arg);
long	ft_atol(const char *str);
t_phil	*init_phils(t_data *data);
