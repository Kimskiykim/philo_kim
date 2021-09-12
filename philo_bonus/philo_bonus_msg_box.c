#include "philo_bonus_headers.h"

void	philo_status_pub(t_philo *phi, char type)
{
	const char	*m;
	t_dat		*dat;
	long long	out;

	dat = phi->dat;
	sem_wait(dat->glob_print);
	m = "is died";
	if (type == 'f')
		m = "has taken a fork";
	else if (type == 'e')
		m = "is eating";
	else if (type == 's')
		m = "is sleeping";
	else if (type == 't')
		m = "is thinking";
	out = philo_time_get() - dat->start_time;
	printf("%lld %d %s\n", out, phi->philo_num, m);
	sem_post(dat->glob_print);
}
