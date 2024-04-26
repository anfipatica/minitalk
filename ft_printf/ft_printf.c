/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:30:57 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 15:30:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	if (c)
		return (write(1, &c, 1));
	else
		return (0);
}

int	ft_putstr(char *str)
{
	int	i;
	int	printed_chars;

	i = -1;
	printed_chars = 0;
	while (str[++i])
		printed_chars += ft_putchar(str[i]);
	return (printed_chars);
}

int	ft_checkarg(char arg, va_list vargs)
{
	int	printed_chars;

	printed_chars = 0;
	if (arg == 'c')
		printed_chars += ft_putchar(va_arg(vargs, int));
	else if (arg == 's')
		printed_chars += ft_putstr(va_arg(vargs, char *));
	else if (arg == 'p')
	{
		write(1, "0x", 2);
		printed_chars += ft_puthexptr(va_arg(vargs, uintptr_t), 2,
				"0123456789abcdef");
	}
	else if (arg == 'd' || arg == 'i')
		printed_chars += ft_putdec(va_arg(vargs, int), 0, "0123456789");
	else if (arg == 'u')
		printed_chars += ft_putudec(va_arg(vargs, unsigned int), 0,
				"0123456789");
	else if (arg == 'x')
		printed_chars += ft_puthex(va_arg(vargs, unsigned int), 0,
				"0123456789abcdef");
	else if (arg == 'X')
		printed_chars += ft_puthex(va_arg(vargs, unsigned int), 0,
				"0123456789ABCDEF");
	return (printed_chars);
}

int	ft_printf(char const *str, ...)
{
	int		i;
	int		printed_chars;
	va_list	vargs;

	i = 0;
	printed_chars = 0;
	va_start(vargs, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '%' && str[i + 1] != '\0')
		{
			printed_chars += ft_checkarg(str[++i], vargs);
		}
		else
			printed_chars += ft_putchar(str[i]);
		i++;
	}
	return (printed_chars);
}

// int	main(void)
// {
// 	char c = 'a';
// 	char *s = "todes";
// 	int d = -456455;
// 	int n = ft_printf("Hola \n%c %s %p %d %i %u %x %X %%", c,
// 		s, &c, d, d, d, d, d);
// 	printf("\nMi printf devuelve: %d\n", n);
// 	int n2 = printf("Hola \n%c %s %p %d %i %u %x %X %%",
// 		c, s, &c, d, d, d, d, d);
// 	printf("\n printf devuelve:%d\n", n2);
// }