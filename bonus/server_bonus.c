/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:32:24 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/24 00:07:14 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

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

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

char	*ft_realloc(char *c, char *str)
{
	char		*temp;
	temp = NULL;
	
	if (!str)
	{
		str = ft_calloc(2, sizeof(char));
		if (!str)
			exit(1);
		str[0] = c[0];
	}
	else
	{
		temp = ft_strdup(str);
		ft_free(&str);
		str = ft_strjoin(temp, c);
		ft_free(&temp);
	}
	return (str);
}

char	decode_length(int signal)
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
			state = message;
			return ('\0');
		}
		else
			return (c);
	}
	return ('\0');
}


void	handle_signal(int signal)
{
	//int str_length;
	static char str_length_char;

	if (state == length)
	{
		printf("jeje\n");
		str_length_char = decode_length(signal);
		ft_printf("->%s\n", str_length_char);
		str_length_char++;
		printf("Se spone que estamos acá\n");
		ft_printf("%s\n", str_length_char);
	}
	else if (state == message)
		ft_printf("Hola\n");
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