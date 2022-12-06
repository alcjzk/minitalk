/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:37:59 by tjaasalo          #+#    #+#             */
/*   Updated: 2022/12/05 19:20:42 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "client.h"

void	sig(pid_t pid, int sig)
{
	if (kill(pid, sig) != 0)
		exit(ft_printf("Signal could not be sent!\n"));
}

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGUSR2)
		exit(ft_printf("Message could not be delivered!\n"));
	g_sig = sig;
}

void	send_start(pid_t pid)
{
	g_sig = 0;
	ft_printf("Waiting for server ACK\n");
	while (!g_sig)
	{
		sig(pid, SIGUSR1);
		usleep(100);
	}
}

int	run(int argc, char **argv)
{
	pid_t	server_pid;
	size_t	size;

	if (argc != 3)
		return (ft_printf("Invalid number of arguments!\n"));
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		return (ft_printf("Invalid pid!\n"));
	size = ft_strlen(argv[2]) + 1;
	if (size == 1)
		return (ft_printf("Skipping string of length 0\n"));
	ft_printf("Server pid: %i\n", server_pid);
	ft_printf("Client pid: %i\n", getpid());
	send_start(server_pid);
	send_size(server_pid, size);
	send_str(server_pid, argv[2]);
	ft_printf("Send OK!\n");
	return (0);
}

int	main(int argc, char **argv)
{
	struct sigaction	action;

	action.sa_sigaction = handle_signal;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&(action.sa_mask));
	sigaddset(&(action.sa_mask), SIGUSR1);
	sigaddset(&(action.sa_mask), SIGUSR2);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	return (run(argc, argv));
}
