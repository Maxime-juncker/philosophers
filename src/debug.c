/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:51:52 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/18 13:09:23 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	debug_color(const char *msg, const char *color)
{
	printf("%s%s\033[0m\n", color, msg);
}

void	success(const char *msg)
{
	debug_color(msg, GREEN);
}

void	warning(const char *msg)
{
	debug_color(msg, YELLOW);
}

void	alert(const char *msg)
{
	debug_color(msg, B_RED);
}

void	error(const char *msg)
{
	debug_color(msg, RED);
}
