#include "philo_bonus_headers.h"

void	philo_parse(int argc, char **argv, t_dat *dat)
{
	philo_init(dat);
	dat->number_of_philosophers = ft_atoi(argv[1]);
	dat->time_to_die = ft_atoi(argv[2]);
	dat->time_to_eat = ft_atoi(argv[3]);
	dat->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		dat->number_must_eat = ft_atoi(argv[5]);
		dat->feeding_mode = 1;
	}	
}

void	philo_init(t_dat *dat)
{
	dat->number_of_philosophers = 0;
	dat->iter = 0;
	dat->time_to_die = 0;
	dat->time_to_eat = 0;
	dat->time_to_sleep = 0;
	dat->number_must_eat = 0;
	dat->all_live = 1;
	dat->feeding_mode = 0;
	dat->philo.dat = dat;
	dat->philo.cur_forks = 0;
	dat->philo.number_eaten = 0;
	sem_unlink(PHILO_FORKS_N);
	sem_unlink(PHILO_DEATH_2);
	sem_unlink(PHILO_EATEN_N);
	sem_unlink(PHILO_PRINT_2);
}
