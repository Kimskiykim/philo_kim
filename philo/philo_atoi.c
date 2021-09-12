#include "philo_headers.h"

static void	simple_tr(const char *str, int *i, unsigned long *z)
{
	while (*str >= '0' && *str <= '9')
	{
		(*z) = (*z) * 10 + (*str - '0');
		str++;
		(*i)++;
	}
}

static void	simple_ut(int sign, int *output, const char *max)
{
	if (sign > 0)
	{
		*output = -1;
		max = "9223372036854775806";
	}
	else
	{
		*output = 0;
		max = "9223372036854775806";
	}
}

static int	lim(const char *st, int i, int sign, unsigned long c)
{
	const char	*max;
	int			counter;
	int			output;

	max = NULL;
	simple_ut(sign, &output, max);
	counter = 0;
	if (i > 19)
		return (output);
	else if (i == 19)
	{
		while (counter < 19)
		{
			if (max[counter] - st[counter] > 0)
				return ((int)c * sign);
			if (max[counter] - st[counter] < 0)
				return (output);
			counter++;
		}
	}
	return ((int)c * sign);
}

int	ft_atoi(const char *str)
{
	int				j;
	int				i;
	unsigned long	z;

	z = 0;
	j = 1;
	i = 0;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			j = -1;
		str++;
	}
	while (*str && *str == '0')
		str++;
	simple_tr(str, &i, &z);
	return (lim(str - i, i, j, z));
}
