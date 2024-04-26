/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:32:17 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/26 15:26:23 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.h"
int	j = 0;

void	check_received(int signal)
{
	(void)signal;
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
		usleep(20);
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
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;
	struct sigaction sa;

	if (argc != 3)
		return (1);
	sa.__sigaction_u.__sa_handler = check_received;
	sa.sa_flags = 0;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	i = -1;
	pid = ft_atoi(argv[1]);
	send_str_length(pid, argv[2]);
	while (argv[2][++i])
		send_char(pid, argv[2][i]);
	send_char(pid, argv[2][i]);
	ft_printf("--------------------------------------------\n"
	"->str chars sent: %d.\n"
	"->total chars sent (str + str_length): %d\n"
	"->chars correctly sent: %d\n"
	"->total confirmations received from server: %d\n"
	"--------------------------------------------\n", i + 1, ((j / 8) - i) + i, (j / 8), j);
	return (0);
}
