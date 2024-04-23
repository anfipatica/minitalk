/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:29:13 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/22 18:18:46 by ymunoz-m         ###   ########.fr       */
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

void	handle_signal(int signal, siginfo_t *info, void *ucontext)
{
	static int	byte;
	static char	c[2];
	static char	*str;

	(void)ucontext;
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
	usleep(50);
	kill(info->si_pid, signal);
}


int	main(void)
{
	struct sigaction	sa;

	print_pid();
	sa.__sigaction_u.__sa_sigaction = handle_signal;
	sa.sa_flags = 0;
	sa.sa_mask = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		;
	return (0);
}
