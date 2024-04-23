/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:32:24 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/23 22:18:48 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

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

void	handle_signal(int signal)
{
	static int	byte;
	static char	c[2];
	static char	*str;

	if (byte == 0 || byte == 0b10000000)
	{
		byte = 0b00000001;
		c[0] = 0b00000000;
		c[1] = '\0';
	}
	else
		byte <<= 1;
	if (signal == SIGUSR1)
		c[0] |= byte;
	if (byte == 0b10000000)
	{
		if (c[0] == '\0')
		{
			write(1, str, ft_strlen(str));
			write(1, "\n", 1);
			ft_free(&str);
		}
		else
			str = ft_realloc(c, str);
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
