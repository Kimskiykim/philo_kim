#include "philo_headers.h"

void	philo_cleaner_forks(pthread_mutex_t	**forks, int n)
{
	int	i;

	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			pthread_mutex_destroy(forks[i]);
			free(forks[i]);
			i++;
		}
	}
	free(forks);
}

void	philo_cleaner_philo(t_philo **philo, int n)
{
	int	i;

	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			free(philo[i]);
			i++;
		}
	}
	free(philo);
}

pthread_mutex_t	**philo_create_forks(int n)
{
	pthread_mutex_t	**forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t *) * (n));
	if (forks == NULL)
		return (NULL);
	forks[n] = NULL;
	while (i < n)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (forks[i] == NULL)
		{
			philo_cleaner_forks(forks, i);
			break ;
		}
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo	**philo_create_philo(int num, t_dat *dat)
{
	t_philo	**philo;
	int		i;

	philo = (t_philo **)malloc(sizeof(t_philo *) * (num));
	if (philo == NULL)
		return (NULL);
	i = 0;
	while (i < num)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (philo[i] == NULL)
		{
			philo_cleaner_philo(philo, i);
			break ;
		}
		philo[i]->philo_num = i + 1;
		philo[i]->odd = (i + 1) % 2;
		philo[i]->dat = dat;
		i++;
	}
	return (philo);
}
