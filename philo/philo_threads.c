#include "philo_headers.h"

static void	philo_run_threads(pthread_t *philo_thread, t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->number_of_philosophers)
	{
		dat->start_time = philo_time_get();
		pthread_create(&philo_thread[i], NULL, philo_death_game, dat->philo[i]);
		philo_sleep25(1);
		i += 2;
	}
	i = 1;
	while (i < dat->number_of_philosophers)
	{
		dat->start_time = philo_time_get();
		pthread_create(&philo_thread[i], NULL, philo_death_game, dat->philo[i]);
		philo_sleep25(1);
		i += 2;
	}
}

static void	philo_checker(t_dat *dat)
{
	int			i;
	long long	time;
	long long	diff;

	while (dat->all_live == 1)
	{
		i = -1;
		while (++i < dat->number_of_philosophers && dat->all_live == 1)
		{
			time = philo_time_get();
			if (dat->philo[i]->last_meal_time == 0)
				continue ;
			diff = time - dat->philo[i]->last_meal_time;
			if (diff > dat->time_to_die)
			{
				pthread_mutex_lock(&dat->mut_death);
				philo_status_pub(dat->philo[i], 'd');
				dat->all_live = 0;
				break ;
			}
		}
	}
}

static void	check_eaten(t_dat *dat)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < dat->number_of_philosophers)
	{
		if (dat->philo[i]->number_eaten >= dat->number_must_eat)
			j++;
		i++;
	}
	if (j == dat->number_of_philosophers)
	{
		pthread_mutex_lock(&dat->mut_death);
		printf("%lld They're well-fed\n", philo_time_get() - dat->start_time);
		dat->all_live = 0;
	}
}

static void	philo_checker_eaten(t_dat *dat)
{
	int			i;
	long long	time;
	long long	diff;

	while (dat->all_live == 1)
	{
		i = -1;
		while (++i < dat->number_of_philosophers && dat->all_live == 1)
		{
			time = philo_time_get();
			if (dat->philo[i]->last_meal_time == 0)
				continue ;
			diff = time - dat->philo[i]->last_meal_time;
			if (diff > dat->time_to_die)
			{
				pthread_mutex_lock(&dat->mut_death);
				philo_status_pub(dat->philo[i], 'd');
				dat->all_live = 0;
				break ;
			}
		}
		check_eaten(dat);
	}
}

int	philo_threads(t_dat *dat)
{
	pthread_t	*philo_thread;
	int			i;

	philo_thread = malloc(sizeof(pthread_t) * dat->number_of_philosophers);
	if (!philo_thread)
		return (-1);
	philo_run_threads(philo_thread, dat);
	i = -1;
	while (++i < dat->number_of_philosophers)
		pthread_detach(philo_thread[i]);
	if (dat->feeding_mode == 0)
		philo_checker(dat);
	else
		philo_checker_eaten(dat);
	free(philo_thread);
	return (0);
}
