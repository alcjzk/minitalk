/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjaasalo <tjaasalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:55:11 by tjaasalo          #+#    #+#             */
/*   Updated: 2022/12/05 19:10:36 by tjaasalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <signal.h>

volatile int	g_sig;

void	send_ibit(pid_t pid, int val, int idx);
void	send_cbit(pid_t pid, char val, int idx);
void	send_char(pid_t pid, char c);
void	send_size(pid_t pid, int size);
void	send_str(pid_t pid, char *str);

void	sig(pid_t pid, int sig);
void	handle_signal(int sig, siginfo_t *info, void *ucontext);
void	send_start(pid_t pid);

#endif
