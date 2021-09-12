#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H
# include "philo_headers.h"

typedef struct s_philo
{
	int				philo_num;
	long long		cur_time;
	long long		last_meal_time;
	int				number_eaten;
	int				odd;			
	struct s_dat	*dat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

}					t_philo;

typedef struct s_dat
{
	int				number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_must_eat;
	long long		start_time;
	int				all_live;
	int				feeding_mode;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_death;
	pthread_mutex_t	**forks;
	t_philo			**philo;
}					t_dat;
#endif
