/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 00:10:27 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:22:26 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	nb_length(long number)
{
	int	count;

	count = 0;
	if (number == 0)
		return (1);
	while (number > 0)
	{
		number /= 10;
		count++;
	}
	return (count);
}

static char	*save_number(char *memory, long number, int sign)
{
	size_t	index;

	index = sign + nb_length(number);
	memory[index] = '\0';
	while (number > 0)
	{
		memory[index - 1] = (number % 10) + '0';
		number /= 10;
		index --;
	}
	if (sign == 1)
		memory[0] = '-';
	return (memory);
}

char	*ft_itoa(int n)
{
	int		sign;
	long	number;
	char	*memory;

	number = n;
	sign = 0;
	if (number < 0)
	{
		sign = 1;
		number *= -1;
	}
	memory = (char *) malloc((sign + nb_length(number) + 1) * sizeof(char));
	if (!memory)
		return (NULL);
	if (number == 0)
		memory[0] = '0';
	return (save_number(memory, number, sign));
}
