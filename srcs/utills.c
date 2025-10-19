#include "philosophers.h"

void	safe_print(t_phil *phil, char *action)
{
	long	time;

	if (is_dead(phil->data))
		return ;
	time = get_timestamp() - phil->data->start_time;
	pthread_mutex_lock(&phil->data->print);
	printf("%ld %d %s\n", time, phil->id, action);
	pthread_mutex_unlock(&phil->data->print);
}

int	ft_log(char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
	write(1, "\n", 1);
	return (1);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] == ' ') || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (0);
		i++;
	}
	data->num_phil = ft_atol(argv[1]);
	data->time_die = ft_atol(argv[2]);
	data->time_eat = ft_atol(argv[3]);
	data->time_slp = ft_atol(argv[4]);
	data->must_eaten = -1;
	if (argc == 6)
		data->must_eaten = ft_atol(argv[5]);
	if (data->num_phil <= 0)
		return (0);
	if (data->time_die <= 0 || data->time_eat <= 0 || data->time_slp <= 0)
		return (0);
	return (1);
}
