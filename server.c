/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-masc <ldi-masc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:42:33 by ldi-masc          #+#    #+#             */
/*   Updated: 2022/10/03 10:58:39 by ldi-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler_s(int sig, siginfo_t *siginfo, void *optional)
{
	static unsigned char	c;
	static int				i;

	(void)optional;
	(void)siginfo;
	c = c | (sig == SIGUSR1);
	if (++i == 8)
	{
		i = 0;
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
