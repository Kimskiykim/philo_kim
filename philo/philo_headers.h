#ifndef PHILO_HEADERS_H
# define PHILO_HEADERS_H

# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include "philo_structs.h"

void			philo_init(t_dat *dat);
void			philo_parse(int argc, char **argv, t_dat *dat);
int				philo_table_init(t_dat *dat);
void			philo_fgiver(t_philo **philo, pthread_mutex_t **forks, int n);
void			philo_cleaner_forks(pthread_mutex_t **forks, int n);
void			philo_cleaner_philo(t_philo **philo, int n);
pthread_mutex_t	**philo_create_forks(int n);
t_philo			**philo_create_philo(int num, t_dat *dat);
int				philo_threads(t_dat *dat);
void			*philo_death_game(void *phi);
void			philo_eat(t_dat *dat, t_philo *phi);
void			philo_sleep(t_dat *dat, t_philo *phi);
void			philo_get_fork(t_philo *philo, t_dat *dat);
int				ft_atoi(const char *str);
long long		philo_time_get(void);
void			philo_message(int t_ms, int philo_n, char type);
void			philo_status_pub(t_philo *phi, char type);
void			ft_usleep(useconds_t time);
void			philo_sleep25(int n);
#endif
