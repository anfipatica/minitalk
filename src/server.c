/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:32:24 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/24 21:50:22 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"
#include <time.h>

t_bool	state = length;

void	print_pid(void)
{
	pid_t	pid;

	pid = getpid();

	ft_printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n"
				"\n	|￣￣￣￣￣￣￣￣￣|\n"
				"	|       PID:       |\n"
				"	|      %d       |\n"
				"	|＿＿＿＿＿＿＿＿＿|\n"
				"	(\\__/) ||\n"
				"	(•ㅅ•) ||\n"
				"	/ 　 づ||\n\n"
				"￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n\n", pid);
}

char	decode_char(int signal)
{
	static int	byte;
	static char	c;

	if (byte == 0 || byte == 0b10000000)
	{
		byte = 0b00000001;
		c = 0b00000000;
	}
	else
		byte <<= 1;
	if (signal == SIGUSR1)
		c |= byte;
	if (byte == 0b10000000)
	{
		if (c == '\0')
		{
			state = !state;
			return ('\0');
		}
		else
			return (c);
	}
	return ('\0');
}

void	decode_str(int signal, char	*str_length_char, int *i)
{
	static char	*str;

	if (!str)
	{
		str = ft_calloc(ft_atoi(str_length_char) + 1, sizeof(char));
		ft_bzero(str_length_char, 7);
		*i = 0;
	}
	str[*i] = decode_char(signal);
	//printf("i = %d, state = %d. str[i] = \"%c\"\n", *i, state, str[*i]);
	if (state == length)
	{
		printf("%s\n", str);
		free(str);
		str = NULL;
		*i = 0;
	}
	else if (str[*i] != '\0')
		(*i)++;
}
void	handle_signal(int signal)
{
	static char	str_length_char[7];
	static int	i;
	//printf("i = %d\n", i);
	//printf("-->state = %u\n", state);
	if (!i)
	{
		i = 0;
	}
	if (state == length)
	{
		str_length_char[i] = decode_char(signal);
		//printf("c = %c\n", str_length_char[i]);
		if (str_length_char[i] != '\0')
			i++;
	}
	else
	{
		decode_str(signal, str_length_char, &i);
	}
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			mask;
	print_pid();
	sigemptyset(&mask);
	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	sa.sa_mask = mask;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		;
	return (0);
}
