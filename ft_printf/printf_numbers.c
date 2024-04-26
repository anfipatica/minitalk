/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:00:03 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 23:00:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexptr(uintptr_t number, int printed_chars, char *str)
{
	if (number / 16 != 0)
	{
		printed_chars = ft_puthexptr(number / 16, printed_chars, str);
		ft_putchar(str[number % 16]);
	}
	else
		ft_putchar(str[number % 16]);
	return (++printed_chars);
}

int	ft_puthex(unsigned int number, int printed_chars, char *str)
{
	if (number / 16 != 0)
	{
		printed_chars = ft_puthex(number / 16, printed_chars, str);
		ft_putchar(str[number % 16]);
	}
	else
		ft_putchar(str[number % 16]);
	return (++printed_chars);
}

int	ft_putdec(int number, int printed_chars, char *str)
{
	if (number < 0 && number != -2147483648)
	{
		number *= -1;
		printed_chars = ft_putchar('-');
	}
	if (number == -2147483648)
		printed_chars = write(1, "-2147483648", 11) - 1;
	else if (number / 10 != 0)
	{
		printed_chars = ft_putdec(number / 10, printed_chars, str);
		ft_putchar(str[number % 10]);
	}
	else
		ft_putchar(str[number % 10]);
	return (++printed_chars);
}

int	ft_putudec(unsigned int number, int printed_chars, char *str)
{
	if (number / 10 != 0)
	{
		printed_chars = ft_putudec(number / 10, printed_chars, "0123456789");
		ft_putchar(str[number % 10]);
	}
	else
		ft_putchar(str[number % 10]);
	return (++printed_chars);
}
