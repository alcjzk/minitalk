/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:47:22 by tjaasalo          #+#    #+#             */
/*   Updated: 2022/12/05 19:08:21 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "server.h"

int	recv_size(void)
{
	int		size;
	int		bits;

	size = 0;
	bits = sizeof(int) * 8;
	while (1)
	{
		if (!g_sigstate.sig)
			usleep(1);
		else
		{
			bits--;
			if (g_sigstate.sig == SIGUSR1)
				size |= 1 << bits;
			ack(g_sigstate.pid);
			if (!bits)
				return (size);
		}
	}
}

char	recv_char(void)
{
	char	c;
	int		bits;

	c = 0;
	bits = sizeof(char) * 8;
	while (1)
	{
		if (!g_sigstate.sig)
			usleep(1);
		else
		{
			bits--;
			if (g_sigstate.sig == SIGUSR1)
				c |= 1 << bits;
			ack(g_sigstate.pid);
			if (!bits)
				return (c);
		}
	}
}

char	*recv_str(int size)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(size);
	if (!str)
		return (NULL);
	while (i < size)
		str[i++] = recv_char();
	return (str);
}

void	recv_start(void)
{
	while (1)
	{
		if (!g_sigstate.sig)
			usleep(1);
		else
			return (ack(g_sigstate.pid));
	}
}
