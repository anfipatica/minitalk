/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:00:19 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 23:00:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H /*This is an id*/
# define FT_PRINTF_H
# include <stdarg.h> //library for av_ macros
# include <unistd.h>
# include <stdint.h> //library for uintptr_t

int	ft_printf(char const *str, ...);
int	ft_checkarg(char arg, va_list vargs);
int	ft_putstr(char *str);
int	ft_putchar(char c);

int	ft_puthexptr(uintptr_t number, int printed_chars, char *str);
int	ft_puthex(unsigned int number, int printed_chars, char *str);
int	ft_putdec(int number, int printed_chars, char *str);
int	ft_putudec(unsigned int number, int printed_chars, char *str);

#endif