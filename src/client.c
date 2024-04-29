/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:32:17 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/29 19:32:42 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.h"
#include <time.h>

int	g_j = 0;

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
		g_j++;
		if (g_j % 16000 == 0 && g_j != 0)
			ft_printf(".\n\n");
		else if (g_j % 8000 == 0 && g_j != 0)
			ft_printf("..\n\n");
		usleep(45);
	}
}

void	send_str_length(pid_t server_pid, char *str)
{
	char	*str_length;
	int		i;

	str_length = ft_itoa(ft_strlen(str));
	i = -1;
	while (str_length[++i])
	{
		send_char(server_pid, str_length[i]);
	}
	send_char(server_pid, str_length[i]);
	free(str_length);
	str_length = NULL;
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (argc != 3)
		return (1);
	i = -1;
	pid = ft_atoi(argv[1]);
	send_str_length(pid, argv[2]);
	while (argv[2][++i])
		send_char(pid, argv[2][i]);
	send_char(pid, argv[2][i]);
	return (0);
}
