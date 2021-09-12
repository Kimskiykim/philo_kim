#include "philo_bonus_headers.h"

static int	philo_input_check(t_dat *dat)
{
	if (dat->time_to_die < 0 || dat->time_to_eat < 0)
		return (0);
	if (dat->number_of_philosophers <= 0 || dat->time_to_sleep < 0)
		return (0);
	if (dat->feeding_mode == 1 && dat->number_must_eat <= 0)
		return (0);
	dat->pid = malloc(sizeof(int) * (dat->number_of_philosophers));
	if (dat->pid == NULL)
		return (0);
	dat->glob_forks = sem_open(PHILO_FORKS_N, O_CREAT, \
	777, dat->number_of_philosophers);
	dat->glob_death = sem_open(PHILO_DEATH_2, O_CREAT, 777, 1);
	dat->glob_print = sem_open(PHILO_PRINT_2, O_CREAT, 777, 1);
	if (dat->feeding_mode == 1)
		dat->glob_eaten = sem_open(PHILO_EATEN_N, O_CREAT, 777, 0);
	return (1);
}

static int	simple_util(t_dat *dat, int mode)
{
	if (mode == 1)
		printf("Wrong input\n");
	else if (mode == 7)
	{
		sem_close(dat->glob_forks);
		sem_close(dat->glob_death);
		sem_close(dat->glob_print);
		if (dat->feeding_mode == 1)
			sem_close(dat->glob_eaten);
		sem_unlink(PHILO_FORKS_N);
		sem_unlink(PHILO_DEATH_2);
		sem_unlink(PHILO_PRINT_2);
		sem_unlink(PHILO_EATEN_N);
		free(dat->pid);
	}
	free(dat);
	return (0);
}

void	killer_util(t_dat *dat)
{
	dat->iter = 0;
	while (dat->iter < dat->number_of_philosophers)
	{
		kill(dat->pid[dat->iter], SIGKILL);
		(dat->iter)++;
	}
}

static void	philo_sauron(t_dat *dat)
{
	pthread_t		watcher[2];

	dat->fin_check = 1;
	pthread_mutex_init(&dat->mut_end, NULL);
	pthread_create(&watcher[0], NULL, philo_watcher_error, dat);
	if (dat->feeding_mode == 1)
		pthread_create(&watcher[1], NULL, philo_watcher_eat, dat);
	pthread_detach(watcher[0]);
	if (dat->feeding_mode == 1)
		pthread_detach(watcher[1]);
	while (dat->fin_check == 1)
		philo_sleep25(4);
	pthread_mutex_destroy(&dat->mut_end);
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
		while (dat->iter < dat->number_of_philosophers)
		{
			dat->pid[dat->iter] = fork();
			if (dat->pid[dat->iter] == 0)
				philo_threads(dat);
			(dat->iter)++;
		}
		philo_sauron(dat);
		simple_util(dat, 7);
		return (1);
	}
	printf("Wrong input\n");
	return (0);
}
