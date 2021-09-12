#include "philo_headers.h"

static void	philo_killer(t_dat *dat)
{
	philo_cleaner_forks(dat->forks, dat->number_of_philosophers);
	philo_cleaner_philo(dat->philo, dat->number_of_philosophers);
	pthread_mutex_destroy(&dat->mut_print);
	pthread_mutex_destroy(&dat->mut_death);
	free(dat);
	dat = NULL;
}

static int	philo_input_check(t_dat *dat)
{
	if (dat->time_to_die < 0 || dat->time_to_eat < 0)
		return (0);
	if (dat->number_of_philosophers <= 0 || dat->time_to_sleep < 0)
		return (0);
	if (dat->feeding_mode == 1)
	{
		if (dat->number_must_eat <= 0)
			return (0);
	}
	return (1);
}

static int	simple_util(t_dat *dat, int wrong_input)
{
	if (wrong_input == 1)
		printf("Wrong input\n");
	free(dat);
	return (0);
}

int	main(int argc, char **argv)
{
	t_dat		*dat;

	dat = NULL;
	if (argc > 4 && argc < 7)
	{
		dat = (t_dat *)malloc(sizeof(t_dat));
		if (dat == NULL)
			return (-1);
		philo_parse(argc, argv, dat);
		if (!philo_input_check(dat))
			return (simple_util(dat, 1));
		if (philo_table_init(dat) == 0)
			return (simple_util(dat, 0));
		philo_threads(dat);
		philo_killer(dat);
		return (1);
	}
	printf("Wrong input\n");
	return (0);
}
