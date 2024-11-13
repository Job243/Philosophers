/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:52:25 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/13 20:13:18 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_digit(char c)
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
	{
		num = num * 10 + *str++ - 48;
	}
	if (num > INT_MAX)
		return (0);
	return (num);
}
