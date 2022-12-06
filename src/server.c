/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:37:32 by tjaasalo          #+#    #+#             */
/*   Updated: 2022/12/05 19:20:19 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "server.h"

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (!g_sigstate.pid)
		g_sigstate.pid = info->si_pid;
	g_sigstate.sig = sig;
}

void	ack(pid_t pid)
{
	g_sigstate.sig = 0;
	kill(pid, SIGUSR1);
}

void	run(void)
{
	int		size;
	char	*str;

	while (1)
	{
		ft_printf("Waiting for message\n");
		ft_printf("Server pid: %i\n", getpid());
		recv_start();
		size = recv_size();
		ft_printf("Received size: %i\n", size);
		str = recv_str(size);
		if (str)
		{
			ft_printf(">>> MESSAGE >>>\n%s\n<<< MESSAGE <<<\n\n", str);
			free(str);
		}
		else
		{
			ft_printf("Failed to alloc for message!\n");
			kill(g_sigstate.pid, SIGUSR2);
		}
		g_sigstate.pid = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	g_sigstate.pid = 0;
	g_sigstate.sig = 0;
	action.sa_sigaction = handler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&(action.sa_mask));
	sigaddset(&(action.sa_mask), SIGUSR1);
	sigaddset(&(action.sa_mask), SIGUSR2);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	run();
	return (0);
}
