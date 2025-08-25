#include "philosophers.h"

void ft_log(char* s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
    write(1, "\n", 1);
}
long ft_atol(const char *str)
{
    int		i;
    long	result;
    int		sign;

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
