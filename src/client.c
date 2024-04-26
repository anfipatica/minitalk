/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:32:17 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/26 14:21:05 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.h"
#include <time.h>
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
			ft_printf(".\n\n");
		else if (j % 8000 == 0 && j != 0)
			ft_printf("..\n\n");
		usleep(45);
	}
}

void	send_str_length(pid_t server_pid, char *str)
{
	char	*str_length;
	int		i;

	str_length = ft_itoa(ft_strlen(str));
	printf("%s\n", str_length);
	i = -1;
	while (str_length[++i])
	{
		send_char(server_pid, str_length[i]);
	}
	send_char(server_pid, str_length[i]);
}

int	main(int argc, char **argv)
{

	clock_t start, end;
    double cpu_time_used;

    start = clock();

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

	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("El tiempo de CPU usado es: %f segundos\n", cpu_time_used);
	return (0);
}