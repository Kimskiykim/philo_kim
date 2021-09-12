#ifndef PHILO_BONUS_HEADERS_H
# define PHILO_BONUS_HEADERS_H
# define PHILO_FORKS_N "/semp_forks"
# define PHILO_PRINT_2 "/semp_print"
# define PHILO_DEATH_2 "/semp_death"
# define PHILO_EATEN_N "/semp_death"

# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <semaphore.h>
# include <signal.h>
# include "philo_bonus_structs.h"

void			philo_init(t_dat *dat);
void			philo_parse(int argc, char **argv, t_dat *dat);
int				philo_table_init(t_dat *dat);
int				philo_threads(t_dat *dat);
void			*philo_death_game(void *dat);
void			philo_eat(t_dat *dat, t_philo *phi);
void			philo_sleep(t_dat *dat, t_philo *phi);
void			philo_get_fork(t_philo *philo, t_dat *dat);
int				ft_atoi(const char *str);
long long		philo_time_get(void);
void			philo_message(int t_ms, int philo_n, char type);
void			philo_status_pub(t_philo *phi, char type);
void			*philo_watcher_eat(void *data);
void			*philo_watcher_error(void *data);
void			ft_usleep(useconds_t time);
void			philo_sleep25(int n);
void			killer_util(t_dat *dat);
#endif
