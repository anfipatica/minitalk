/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:43:03 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/26 16:51:44 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

//Definitions needed to properly work in linux. Commented for mac.
//#define _POSIX_C_SOURCE 199309L
//#define _DEFAULT_SOURCE

//Libraries needed to work with signals
# include <signal.h>
# include <sys/types.h>

//write
# include <unistd.h>

//Not sure if needed:
//#include <stdlib.h>
//#include <stdio.h>

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

typedef enum t_boolean
{
	length = 0,
	message = 1
}		t_bool;

void	print_pid(void);
void	ft_free(char **str);
char	*ft_realloc(char *c, char *str);
void	handle_signal(int signal);
void	handle_signal_bonus(int signal, siginfo_t *info, void *ucontext);

#endif