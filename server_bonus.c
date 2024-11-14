/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-masc <ldi-masc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:42:43 by ldi-masc          #+#    #+#             */
/*   Updated: 2022/10/03 10:58:46 by ldi-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	response(unsigned int *c_pid)
{
	kill(*c_pid, SIGUSR1);
	*c_pid = 0;
}

static void	handler_s(int sig, siginfo_t *siginfo, void *optional)
{
	static unsigned char	c;
	static int				i;
	static unsigned int		c_pid;

	(void)optional;
	c_pid = siginfo->si_pid;
	c = c | (sig == SIGUSR1);
	if (++i == 8)
	{
		i = 0;
		if (!c)
			return (response(&c_pid));
		ft_putchar(c);
		c = 0;
	}
	else
		c = c << 1;
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("PID : ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	sa.sa_sigaction = handler_s;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, 0) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, 0) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
