/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:28:20 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/18 10:06:10 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <limits.h>

static int	get_sign(const char *s, int *i)
{
	int	sign;

	sign = 1;
	while (s[*i] == ' ' || (s[*i] >= '\t' && s[*i] <= '\r'))
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	overflow( void )
{
	printf("%snumerical value require%s\n", RED, RESET);
	return (-1);
}

static int	check_error(int n)
{
	if (n < 0)
	{
		printf("%snegative values are forbidden%s\n", RED, RESET);
		return (-1);
	}
	return (n);
}

int	get_settings_val(const char *s)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = get_sign(s, &i);
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (result > INT_MAX / 10)
			return (overflow());
		if (result < INT_MIN / 10)
			return (overflow());
		result *= 10;
		if (result > INT_MAX - (s[i] - '0'))
			return (overflow());
		if (result < INT_MIN + (s[i] - '0'))
			return (overflow());
		if (sign < 0)
			result -= s[i] - '0';
		else
			result += s[i] - '0';
		i++;
	}
	return (check_error(result));
}
