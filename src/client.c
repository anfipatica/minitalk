/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:32:17 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/23 22:19:04 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.h"

int	j = 0;

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
		j++;
		if (j % 16000 == 0 && j != 0)
			ft_printf(".\n\n", j);
		else if (j % 8000 == 0 && j != 0)
			ft_printf("..\n\n", j);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (argc != 3)
		return (1);
	i = -1;
	pid = ft_atoi(argv[1]);
	while (argv[2][++i])
	{
		send_char(pid, argv[2][i]);
	}
	send_char(pid, argv[2][i]);
	return (0);
}
