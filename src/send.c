/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:52:19 by tjaasalo          #+#    #+#             */
/*   Updated: 2022/12/05 19:08:37 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "ft_printf.h"

void	send_ibit(pid_t pid, int val, int idx)
{
	g_sig = 0;
	if ((val & (1 << idx)))
		sig(pid, SIGUSR1);
	else
		sig(pid, SIGUSR2);
}

void	send_cbit(pid_t pid, char val, int idx)
{
	g_sig = 0;
	if ((val & (1 << idx)))
		sig(pid, SIGUSR1);
	else
		sig(pid, SIGUSR2);
}

void	send_char(pid_t pid, char c)
{
	int	bits;

	bits = sizeof(char) * 8;
	send_cbit(pid, c, --bits);
	while (bits)
	{
		if (!g_sig)
			usleep(1);
		else
			send_cbit(pid, c, --bits);
	}
	while (!g_sig)
		usleep(1);
}

void	send_size(pid_t pid, int size)
{
	int	bits;

	ft_printf("Sending string of size: %i\n", size);
	bits = sizeof(int) * 8;
	send_ibit(pid, size, --bits);
	while (bits)
	{
		if (!g_sig)
			usleep(1);
		else
			send_ibit(pid, size, --bits);
	}
	while (!g_sig)
		usleep(1);
}

void	send_str(pid_t pid, char *str)
{
	if (!str)
		return ;
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
}
