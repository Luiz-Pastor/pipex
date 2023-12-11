/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:00:55 by lpastor-          #+#    #+#             */
/*   Updated: 2023/09/12 09:21:41 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

static int	is_space(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t')
		return (1);
	if (ch == '\v' || ch == '\f' || ch == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		count;
	size_t	index;
	int		sign;

	sign = 1;
	count = 0;
	index = 0;
	while (is_space(str[index]))
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		count = (count * 10) + (str[index] - '0');
		index++;
	}
	return (sign * count);
}

int	ft_strict_atoi(const char *str, int *flag)
{
	int		count;
	size_t	index;
	int		sign;

	sign = 1;
	count = 0;
	index = 0;
	*flag = 0;
	while (is_space(str[index]))
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		count = (count * 10) + (str[index] - '0');
		index++;
	}
	if (str[index])
		*flag = -1;
	return (sign * count);
}
