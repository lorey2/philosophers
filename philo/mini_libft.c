/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:53:38 by lorey             #+#    #+#             */
/*   Updated: 2025/01/06 18:57:47 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*number;
	long	num;

	num = n;
	i = ft_intlen(num);
	number = malloc(sizeof(char) * (ft_intlen(num) + 1));
	if (!number)
		return (NULL);
	if (num < 0)
		num = -num;
	while (i > 0)
	{
		number[--i] = num % 10 + 48;
		num = num / 10;
	}
	if (n < 0)
		number[0] = '-';
	number[ft_intlen(n)] = '\0';
	return (number);
}

long long	ft_atoi(const char *str)
{
	long long		i;
	long long		number;
	long long		neg;

	i = 0;
	number = 0;
	neg = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'\
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		number += (str[i] - '0');
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			number *= 10;
		i++;
	}
	return (number *= neg);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

size_t	ft_strlen_skip_zero(const char *s)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] == '0')
		i++;
	while (s[size])
		size++;
	return (size - i);
}
