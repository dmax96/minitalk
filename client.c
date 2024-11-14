/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-masc <ldi-masc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:42:16 by ldi-masc          #+#    #+#             */
/*   Updated: 2022/10/03 10:45:33 by ldi-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr("Wrong input: [pid] [string]\n");
		exit(0);
	}
	send_to_server(ft_atoi(argv[1]), argv[2]);
}
