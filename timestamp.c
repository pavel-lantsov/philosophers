#include "philosophers.h"

long get_timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec *1000 + tv.tv_usec / 1000);
}

void ft_usleep(long ms)
{
    long start;
	start = get_timestamp();
    
    while (get_timestamp() - start < ms)
        usleep(100);
}