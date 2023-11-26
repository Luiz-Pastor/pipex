/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:25:41 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:23:53 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long	number;
	char	aux;
	int		count;

	number = n;
	count = 0;
	if (number < 0)
	{
		count += write(fd, "-", 1);
		number = -number;
	}
	if (number < 10)
	{
		aux = number + '0';
		return (write(fd, &aux, 1));
	}
	count += ft_putnbr_fd(number / 10, fd);
	aux = (number % 10) + '0';
	return (count + write(fd, &aux, 1));
}
