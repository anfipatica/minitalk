/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:31:21 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/22 19:21:42 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#define _POSIX_C_SOURCE 199309L
//#define _DEFAULT_SOURCE
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "../libft/ft_printf.c"
#include "../libft/libft.h"
#include <time.h>

int	j = 0;


void	check_received(int signal)
{
	j++;
	if (j % 16000 == 0 && j != 0)
		ft_printf(".\n\n", j);
	else if (j % 8000 == 0 && j != 0)
		ft_printf("..\n\n", j);
}

void	send_char(int pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & (1 << i))
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(write(1, "ERROR: Incorrect PID. Try again\n", 32));
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(write(1, "ERROR: Incorrect PID. Try again\n", 32));
		}
		pause();
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				pid;
	int					i;

    clock_t start, end;
    double cpu_time_used;

    start = clock();

	if (argc != 3)
		return (1);
	i = -1;
	pid = ft_atoi(argv[1]);
	sa.__sigaction_u.__sa_handler = check_received;
	sa.sa_flags = 0;
	sa.sa_mask = 0;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (argv[2][++i])
	{
		send_char(pid, argv[2][i]);
	}
	send_char(pid, argv[2][i]);
	printf("->chars sent: %lu\n->confirmations received: %d\n\n", ft_strlen(argv[2]) + 1, (j / 8));
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("El tiempo de CPU usado es: %f segundos\n", cpu_time_used);
	return (0);
}
