/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfi <anfi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:30:52 by ymunoz-m          #+#    #+#             */
/*   Updated: 2024/04/23 20:06:47 by anfi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_H
# define CLIENT_H
//Definitions needed to properly work in linux. Commented for mac.
#define _POSIX_C_SOURCE 199309L
#define _DEFAULT_SOURCE

//Libraries needed to work with signals
# include <signal.h>
# include <sys/types.h>
//write
# include <unistd.h>

//Not sure if needed:
//#include <stdlib.h>
//#include <stdio.h>

# include "../libft/libft.h"

void	send_char(int pid, char c);

#endif