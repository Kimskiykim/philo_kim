#include "philo_bonus_headers.h"

void	philo_eat(t_dat *dat, t_philo *phi)
{
	philo_status_pub(phi, 'e');
	ft_usleep(dat->time_to_eat);
	phi->last_meal_time = philo_time_get();
	phi->number_eaten += 1;
	if (dat->feeding_mode == 1)
	{
		if (phi->number_eaten == dat->number_must_eat)
			sem_post(dat->glob_eaten);
	}
}

void	philo_sleep(t_dat *dat, t_philo *phi)
{
	philo_status_pub(phi, 's');
	ft_usleep(dat->time_to_sleep);
}

void	philo_get_fork(t_philo *philo, t_dat *dat)
{
	while (philo->cur_forks < 2)
	{
		sem_wait(dat->glob_forks);
		philo->cur_forks++;
		philo_status_pub(philo, 'f');
	}
	philo_eat(dat, philo);
	while (philo->cur_forks > 0)
	{
		sem_post(dat->glob_forks);
		philo->cur_forks--;
	}
}

void	*philo_death_game(void *data)
{
	t_philo	*philo;
	t_dat	*dat;

	dat = (t_dat *)data;
	philo = &dat->philo;
	philo->philo_num = dat->iter + 1;
	philo->last_meal_time = philo_time_get();
	while (1)
	{
		philo_get_fork(philo, dat);
		philo_sleep(dat, philo);
		philo_status_pub(philo, 't');
	}
	return (NULL);
}
