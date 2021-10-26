/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnaida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:20:03 by gnaida            #+#    #+#             */
/*   Updated: 2021/09/10 16:27:16 by gnaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_time;

void	ft_init_client(char **argv, t_client *inf)
{
	inf->str = argv[2];
	inf->cnt = 128;
	inf->pid = ft_atoi(argv[1]);
}

void	ft_send_signal(int i, t_client *inf)
{
	if (inf->str[i] & inf->cnt)
	{
		if (kill(inf->pid, SIGUSR1) < 0)
		{
			ft_putstr_fd("\nServer is not available!\n", 0);
			exit (0);
		}
	}
	else
	{
		if (kill(inf->pid, SIGUSR2) < 0)
		{
			ft_putstr_fd("\nServer is not available!\n", 0);
			exit (0);
		}
	}
	inf->cnt = inf->cnt / 2;
	usleep(100);
}

void	ft_send_str_by_bit(char **argv)
{
	static t_client	inf;
	static size_t	i;

	if (argv != NULL)
		ft_init_client(argv, &inf);
	if (inf.cnt < 1)
	{
		inf.cnt = 128;
		i++;
	}
	if (i > ft_strlen(inf.str))
	{
		ft_putstr_fd("\nDone!\n", 0);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_send_signal(i, &inf);
	}
}

void	ft_client_handler(int n)
{
	usleep(100);
	if (n != SIGUSR1)
		return ;
	g_time = 0;
	ft_send_str_by_bit(NULL);
}

int	main(int argc, char **argv)
{
	struct sigaction	usr;

	usr.sa_handler = ft_client_handler;
	usr.sa_flags = SA_SIGINFO;
	sigemptyset(&usr.sa_mask);
	sigaddset(&usr.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &usr, NULL);
	if (argc != 3)
	{
		ft_putstr_fd("./client 'server PID' 'message'\n", 0);
		exit(0);
	}
	ft_send_str_by_bit(argv);
	while (1)
	{
		sleep(1);
		if (g_time == 2)
		{
			ft_putstr_fd("\nServer does non answer!\n", 0);
			exit(0);
		}
		g_time++;
	}
	return (0);
}
