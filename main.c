#include "philosophers.h"

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
		return (ft_log("Error: Failed to create monitor thread"));
	return (0);
}

static void	free_all(t_phil *phils, t_data *data)
{
	free(phils);
	free_forks(data->forks, data->num_phil);
	destroy_mutex(data);
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
	while (i < data.num_phil)
	{
		pthread_join(phils[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	free_all(phils, &data);
	return (0);
}
