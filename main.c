#include "philosophers.h"

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

static int	parse_args(int argc, char *argv[], t_data *data)
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

static int	start(t_phil *phil, t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_timestamp();
	while (i < data->num_phil)
	{
		phil[i].lst_meal_time = data->start_time;
		if (pthread_create(&phil[i].thread, NULL, phil_routine, &phil[i]) != 0)
			ft_log("Error: Failed to create thread");
		i++;
	}
	return (0);
}

static int	checker(t_phil *phils, pthread_t *monitor, t_data *data)
{
	if (!phils)
		return (ft_log("Error: Failed to initialize philosophers"));
	if (start(phils, data))
		return (ft_log("Error: Failed to start\n"));
	if (pthread_create(monitor, NULL, death_monitor, phils) != 0)
		ft_log("Error: Failed to create monitor thread");
	return (0);
}

int	main(int argc, char *argv[])
{
	pthread_t	monitor;
	t_data		data;
	t_phil		*phils;
	int			i;

	if (!parse_args(argc, argv, &data))
		return (ft_log("Error: Invalid arguments"));
	data.stop_flag = 0;
	phils = init_phils(&data);
	if (checker(phils, &monitor, &data) != 0)
		return (1);
	i = 0;
	while (i < data.num_phil || data.must_eaten == 0)
	{
		pthread_detach(phils[i].thread);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}
