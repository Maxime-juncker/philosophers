/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:56:45 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/21 09:26:15 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	overflow_feedback(int sign, void *param)
{
	(void)param;
	(void)sign;
	exit(EXIT_FAILURE);
}

int	is_only_digit(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int	check_param_error(int count, char **values)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (overflow_check(values[i], &overflow_feedback, NULL) < 0)
		{
			error("negative values are forbidden!");
			return (1);
		}
		if (!is_only_digit(values[i]))
		{
			error("please only input numbers!");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_errors(int count, char **values)
{
	if (count < 4)
	{
		error("some params are missing");
		return (1);
	}
	if (count > 5)
	{
		error("too much params");
		return (1);
	}
	return (check_param_error(count, values));
}
