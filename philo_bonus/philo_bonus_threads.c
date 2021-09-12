#include "philo_bonus_headers.h"

static void	philo_run_threads(pthread_t *philo_thread, t_dat *dat)
{
	dat->start_time = philo_time_get();
	pthread_create(philo_thread, NULL, philo_death_game, dat);
}

static void	philo_checker(t_dat *dat)
{
	long long	time;
	long long	diff;

	while (dat->all_live == 1)
	{
		time = philo_time_get();
		if (dat->philo.last_meal_time == 0)
			continue ;
		diff = time - dat->philo.last_meal_time;
		if (diff > dat->time_to_die)
		{
			sem_wait(dat->glob_death);
			philo_status_pub(&dat->philo, 'd');
			dat->all_live = 0;
			break ;
		}
	}
}

int	philo_threads(t_dat *dat)
{
	pthread_t	philo_thread;

	philo_run_threads(&philo_thread, dat);
	pthread_detach(philo_thread);
	philo_checker(dat);
	exit(1);
}

void	*philo_watcher_eat(void *data)
{
	t_dat	*dat;
	int		i;

	i = 0;
	dat = (t_dat *)data;
	while (i <= dat->number_of_philosophers)
	{
		sem_wait(dat->glob_eaten);
		i++;
	}
	pthread_mutex_lock(&dat->mut_end);
	if (dat->fin_check == 1)
	{	
		killer_util(dat);
		dat->fin_check = 0;
	}
	pthread_mutex_unlock(&dat->mut_end);
	return (NULL);
}

void	*philo_watcher_error(void *data)
{
	t_dat	*dat;
	int		res;

	res = 0;
	dat = (t_dat *)data;
	waitpid(-1, &res, 0);
	pthread_mutex_lock(&dat->mut_end);
	if (dat->fin_check == 1)
	{	
		killer_util(dat);
		dat->fin_check = 0;
	}
	pthread_mutex_unlock(&dat->mut_end);
	return (NULL);
}
