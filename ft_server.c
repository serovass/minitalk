/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnaida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:28:20 by gnaida            #+#    #+#             */
/*   Updated: 2021/09/10 16:37:03 by gnaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_init_server(t_server *inf)
{
	inf->c = 0;
	inf->cnt = 128;
	inf->pid = 0;
}

void	ft_send_server_reply(int n, t_server *inf)
{
	usleep(100);
	if (n == SIGUSR1)
	{
		inf->c = inf->c + inf->cnt;
		inf->cnt = inf->cnt / 2;
	}
	else if (n == SIGUSR2)
	{
		inf->cnt = inf->cnt / 2;
	}
	if (kill(inf->pid, SIGUSR1) < 0)
		ft_init_server(inf);
}

void	ft_server_handler(int n, siginfo_t *info, void *context)
{
	static t_server	inf;
	static int		t;

	(void)context;
	if (t == 0)
	{
		t = 1;
		ft_init_server(&inf);
	}
	if (inf.pid != 0 && inf.pid != info->si_pid)
		ft_init_server(&inf);
	inf.pid = info->si_pid;
	ft_send_server_reply(n, &inf);
	if (inf.cnt == 0)
	{
		write(1, &inf.c, 1);
		ft_init_server(&inf);
	}
}

int	main(void)
{
	struct sigaction	usr;

	ft_putstr_fd("PID: ", 0);
	ft_putnbr_fd(getpid(), 0);
	ft_putstr_fd("\n", 0);
	usr.sa_sigaction = ft_server_handler;
	usr.sa_flags = SA_SIGINFO;
	sigemptyset(&usr.sa_mask);
	sigaddset(&usr.sa_mask, SIGUSR1);
	sigaddset(&usr.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &usr, NULL);
	sigaction(SIGUSR2, &usr, NULL);
	while (1)
		pause();
	return (0);
}
