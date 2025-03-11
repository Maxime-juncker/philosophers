/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:51:52 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/05 13:44:14 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#if DEBUG

void	debug_color(const char *msg, const char *color)
{
	printf("%s%s\033[0m\n", color, msg);
}
#else

void	debug_color(const char *msg, const char *color)
{
	(void)color;
	(void)msg;
	return ;
}
#endif

void	success(const char *msg)
{
	debug_color(msg, GREEN);
}

void	error(const char *msg)
{
	debug_color(msg, RED);
}

void	alert(const char *msg)
{
	debug_color(msg, B_RED);
}
