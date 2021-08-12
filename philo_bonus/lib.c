/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:10:04 by pyasuko           #+#    #+#             */
/*   Updated: 2021/08/12 17:28:42 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int a)
{
	if (a >= 48 && a <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	flag;

	i = 0;
	res = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		flag = -1;
	else
		flag = 1;
	if (flag == -1 || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (flag * res);
}

void
	ft_putnbr_fd(long n, int fd, int mod)
{
	char	str[13];
	int		nb;

	if (n == 0)
		str[0] = '0';
	nb = 0;
	while (n != 0)
	{
		str[nb++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (nb > 0)
		nb--;
	if (mod)
		write(1, "[", 1);
	while (nb >= 0)
		write(fd, &str[nb--], 1);
	if (mod)
		write(1, "]", 1);
}

int
	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}
