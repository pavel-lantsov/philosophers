#include "philosophers.h"

static int is_valid_number(char *str)
{
	int i;

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

static int parse_args(int argc, char *argv[], t_data *data)
{
	int i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (0);
		i++;
	}
	data->number_of_philosophers = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->number_of_philosophers <= 0)
		return (0);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_phil	*phils;
	int		i;

	if (!parse_args(argc, argv, &data))
	{
		ft_log("Error: Invalid arguments");
		return (1);
	}
	data.stop_flag = 0;
	phils = init_philosophers(&data);
	if (!start(phils, &data))
	{
		ft_log("Error: Failed to start\n");
		return (1);
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_join(phils[i].thread, NULL);
		i++;
	}
	return (0);
}
