/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:25:53 by ymunoz-m          #+#    #+#             */
/*   Updated: 2023/10/04 16:27:44 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char string[])
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

// int	main(void)
// {
// 	printf("Nuestra función devuelve: %lu\n", ft_strlen("holaaaa"));
// 	printf("La función original devuele: %lu", strlen("holaaaa"));
// 	return(0);
// }