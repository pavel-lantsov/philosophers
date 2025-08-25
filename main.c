#include "philosophers.h"

int main(int argc, char *argv[])
{
    t_data data;

    long ts;

    if (!parse_args(argc, argv, &data))
    {
        ft_log("Error: Invalid arguments");
        return (1);
    }
    //Test
    ts = get_timestamp();
    
    printf("Timestamp: %ld \n", get_timestamp());
    ft_usleep(1000);
    printf("Timestamp after: %ld \n", get_timestamp());
    printf("Phil: %d \n", data.number_of_philosophers);
    printf("Time die: %ld \n", data.time_to_die);
    printf("Time eat: %ld \n", data.time_to_eat);
    printf("Time sleep: %ld \n", data.time_to_sleep);

    return (0);
}
