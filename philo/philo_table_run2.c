#include "philo_headers.h"

void	philo_fgiver(t_philo **philo, pthread_mutex_t **forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (i == 0)
			philo[i]->left = forks[n - 1];
		else
			philo[i]->left = forks[i - 1];
		philo[i]->right = forks[i];
		philo[i]->philo_num = i + 1;
		i++;
	}
}

static int	philo_check_table(t_dat *dat)
{
	if (dat->forks == NULL || dat->philo == NULL)
	{
		if (dat->forks)
			philo_cleaner_forks(dat->forks, dat->number_of_philosophers);
		if (dat->philo)
			philo_cleaner_philo(dat->philo, dat->number_of_philosophers);
		pthread_mutex_destroy(&dat->mut_print);
		pthread_mutex_destroy(&dat->mut_death);
		return (0);
	}
	return (1);
}

int	philo_table_init(t_dat *dat)
{
	pthread_mutex_init(&dat->mut_print, NULL);
	pthread_mutex_init(&dat->mut_death, NULL);
	dat->forks = philo_create_forks(dat->number_of_philosophers);
	dat->philo = philo_create_philo(dat->number_of_philosophers, dat);
	if (philo_check_table(dat) == 0)
		return (0);
	philo_fgiver(dat->philo, dat->forks, dat->number_of_philosophers);
	return (1);
}
