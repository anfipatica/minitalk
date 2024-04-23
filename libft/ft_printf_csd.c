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

#include "libft.h"

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
	else if (arg == 'd' || arg == 'i')
		printed_chars += ft_putdec(va_arg(vargs, int), 0, "0123456789");
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
		else if (str[i + 1] != '\0')
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