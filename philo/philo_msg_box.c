#include "philo_headers.h"

void	philo_status_pub(t_philo *phi, char type)
{
	const char	*m;
	t_dat		*dat;
	long long	out;

	dat = phi->dat;
	pthread_mutex_lock(&dat->mut_print);
	if (type != 'd')
	{
		pthread_mutex_lock(&phi->dat->mut_death);
		pthread_mutex_unlock(&phi->dat->mut_death);
	}
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
	pthread_mutex_unlock(&dat->mut_print);
}
