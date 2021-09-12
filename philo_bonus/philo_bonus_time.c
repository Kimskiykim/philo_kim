#include "philo_bonus_headers.h"

long long	philo_time_get(void)
{
	long long		ms;
	struct timeval	tt;

	gettimeofday(&tt, NULL);
	ms = 0;
	ms = tt.tv_sec * 1000 + tt.tv_usec / 1000;
	return (ms);
}

void	philo_sleep25(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		i++;
		usleep(25);
	}
}

void	ft_usleep(useconds_t time)
{
	long long	t;

	t = philo_time_get();
	while (philo_time_get() - t < time)
	{
		if (philo_time_get() - t > time)
			break ;
		usleep(50);
	}
}
