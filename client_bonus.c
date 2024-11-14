/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-masc <ldi-masc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:42:07 by ldi-masc          #+#    #+#             */
/*   Updated: 2022/10/03 10:46:23 by ldi-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_result(int sig, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	(void)sig;
	ft_putstr("Message arrived!\n");
	exit(1);
}

static void	last_bit(int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		if (kill(pid, SIGUSR2) == -1)
			ft_putstr("\nKill failed\n");
		usleep(10);
	}
}

static void	wrong_pid(void)
{
	ft_putstr("Wrong PID\n");
	exit(1);
}

static void	send_to_server(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str;
		while (i--)
		{
			if ((c >> i & 1) != 0)
			{
				if (kill(pid, SIGUSR1) == -1)
					wrong_pid();
			}
			else
				if (kill(pid, SIGUSR2) == -1)
					wrong_pid();
			usleep(50);
		}
		str++;
	}
	last_bit(pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr("Wrong input: [pid] [string]\n");
		exit(0);
	}
	sa.sa_sigaction = ft_result;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, 0) == -1)
		exit(1);
	if (sigaction(SIGUSR2, &sa, 0) == -1)
		exit(1);
	send_to_server(ft_atoi(argv[1]), argv[2]);
	return (0);
}
