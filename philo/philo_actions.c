#include "philo_headers.h"

void	philo_eat(t_dat *dat, t_philo *phi)
{
	philo_status_pub(phi, 'e');
	ft_usleep(dat->time_to_eat);
	phi->last_meal_time = philo_time_get();
	phi->number_eaten += 1;
}

void	philo_sleep(t_dat *dat, t_philo *phi)
{
	philo_status_pub(phi, 's');
	ft_usleep(dat->time_to_sleep);
}

void	philo_get_fork(t_philo *philo, t_dat *dat)
{
	if (philo->odd == 1)
		pthread_mutex_lock(philo->right);
	else
		pthread_mutex_lock(philo->left);
	philo_status_pub(philo, 'f');
	if (philo->odd == 1)
		pthread_mutex_lock(philo->left);
	else
		pthread_mutex_lock(philo->right);
	philo_status_pub(philo, 'f');
	philo_eat(dat, philo);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	*philo_death_game(void *phi)
{
	t_philo	*philo;
	t_dat	*dat;

	philo = (t_philo *)phi;
	dat = (t_dat *)philo->dat;
	philo->last_meal_time = philo_time_get();
	philo->number_eaten = 0;
	while (1)
	{
		philo_get_fork(philo, dat);
		philo_sleep(dat, philo);
		philo_status_pub(philo, 't');
	}
	return (NULL);
}
