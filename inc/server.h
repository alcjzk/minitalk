/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:46:49 by tjaasalo          #+#    #+#             */
/*   Updated: 2022/12/05 19:07:45 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <signal.h>
# include <unistd.h>

typedef struct s_sigstate
{
	volatile int	sig;
	volatile pid_t	pid;
}	t_sigstate;

t_sigstate	g_sigstate;

int		recv_size(void);
char	recv_char(void);
char	*recv_str(int size);
void	recv_start(void);
void	handler(int sig, siginfo_t *info, void *ucontext);
void	ack(pid_t pid);
void	run(void);

#endif
