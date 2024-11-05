/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:52:25 by jmafueni          #+#    #+#             */
/*   Updated: 2024/10/28 17:30:52 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_digit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

const char	*valid_input(const char *str)
{
	int			len;
	const char	*num;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
		return (0);
	if (!is_digit(*str))
		return (0);
	num = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		return (0);
	return (num);
}

long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	if (!str)
		return (0);
	while (is_digit(*str))
		num = num * 10 + *str++ - 48;
	if (num > INT_MAX)
		return (0);
	return (num);
}

int	valid_arg(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		ft_error(RED"ERROR: Wrong input\n"RST G"Usage: <number_of_philosopher>"RST
			G" <time_to_die> <time_to_eat> <time_to_sleep>\n"RST);
	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[i]) <= 0)
			ft_error(RED"ERROR: All arguments must be positive numbers\n"RST);
		i++;
	}
	return (1);
}
