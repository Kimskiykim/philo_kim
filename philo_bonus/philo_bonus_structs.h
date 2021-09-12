#ifndef PHILO_BONUS_STRUCTS_H
# define PHILO_BONUS_STRUCTS_H
# include "philo_bonus_headers.h"

typedef struct s_philo
{
	int				philo_num;
	long long		cur_time;
	long long		last_meal_time;
	int				number_eaten;
	int				odd;
	int				cur_forks;			
	struct s_dat	*dat;

}					t_philo;

typedef struct s_dat
{
	int				number_of_philosophers;
	int				iter;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_must_eat;
	long long		start_time;
	int				all_live;
	int				feeding_mode;
	int				*pid;
	int				fin_check;
	sem_t			*glob_forks;
	sem_t			*glob_print;
	sem_t			*glob_death;
	sem_t			*glob_eaten;
	t_philo			philo;
	pthread_mutex_t	mut_end;
}					t_dat;
#endif
