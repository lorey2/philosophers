/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:13:49 by lorey             #+#    #+#             */
/*   Updated: 2025/01/06 16:02:18 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// ./philosophers nbr_of_philo time_to_die time_to_eat time_to_sleep (nbr meals)

int	ft_isalnum(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		if (ft_strlen_skip_zero(argv[i]) > 10)
			return (write(1, "number too big. MAX_INT is the limit\n", 37), 1);
		j = -1;
		if (argv[i][0] == '+')
			j++;
		while (argv[i][++j])
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (write(1, "only 0 to 9 char and + are ok\n", 30), 1);
	}
	return (0);
}

int	parsing_argv(int argc, char **argv, t_data *data)
{
	int			i;
	long long	temp;

	if (ft_isalnum(argc, argv, data))
		return (1);
	i = 0;
	data->nbr_limit_meals = -1;
	while (++i < argc)
	{
		temp = ft_atoi(argv[i]);
		if (temp > 2147483647)
			return (write(1, "number too big. MAX_INT is the limit", 36), 1);
		(i == 1) && (data->philo_nbr = temp * 1e3);
		(i == 2) && (data->time_to_eat = temp * 1e3);
		(i == 3) && (data->time_to_eat = temp * 1e3);
		(i == 4) && (data->time_to_sleep = temp * 1e3);
		if (i == 5)
			if (argc == 6)
				data->nbr_limit_meals = temp;
	}
	if (data->time_to_eat < 6e4 || data->time_to_sleep < 6e4
		|| data->time_to_die < 6e4)
		return (write(1, "please use time bigger than 60ms", 33), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (parsing_argv(argc, argv, &data))
			return (1);
	}
	else
		return (write(1, "bad prompt (not enough or too many args)\n", 41), \
		write(1, "./philosophers nbr_phi t_die t_eat t_sleep (meals)", 50) \
		, 0);
}
