/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 16:50:16 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:35:40 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	ft_twentyfive(long n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (l + 1);
	if (n < 0)
	{
		n = n * (-1);
		l++;
	}
	while (n > 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char			*str;
	long			nu;
	unsigned int	i;

	nu = n;
	i = ft_twentyfive(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (nu == 0)
		str[0] = 48;
	if (nu < 0)
	{
		str[0] = '-';
		nu = nu * (-1);
	}
	while (nu > 0)
	{
		str[i] = 48 + (nu % 10);
		nu = nu / 10;
		i--;
	}
	return (str);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	buf;
	int	sign;

	i = 0;
	buf = 0;
	sign = 1;
	if (str[i] == '\0')
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		buf = (str[i] - 48) + buf * 10;
		i++;
	}
	return (buf * sign);
}
